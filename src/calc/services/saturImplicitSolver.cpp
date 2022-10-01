#include "saturImplicitSolver.hpp"

#include <cmath>

#include "common/services/commonVector.hpp"
#include "common/services/workRp.hpp"
#include "mesh/models/faceType.hpp"

namespace cs = ble::src::common::services;

namespace ble::src::calc::services {

void print_vector(const std::vector<double>& a, const std::string& nm, const std::string& section)
{
    std::cout << "[" << section << "] " << nm << " = (" << a[0] << "\t" << a[1] << ")" << std::endl;
}

void print_system(const models::DiagMat& mtr, const std::vector<double>& rhs)
{
    int n = rhs.size();
    auto print_row = [&](int ri) {
        if (ri == 0) {
            std::cout << "(" << mtr.C[ri] << "\t" << mtr.B[ri] << ") * () = (" << rhs[ri] << ")" << std::endl;
        } else {
            std::cout << "(" << 0 << "\t" << mtr.C[ri] << ") * () = (" << rhs[ri] << ")" << std::endl;
        }
    };

    for (int k = 0; k < n; k++)
        print_row(k);
}

std::vector<double> SaturImplicitSolverService::solve(double tau, const std::vector<double>& init,
    const std::shared_ptr<common::models::SolverData> data,
    const std::shared_ptr<mesh::models::Grid> grd, bool need_precise)
{
    m_data = data;
    m_init = init;
    m_grd = grd;
    m_tau = tau;

    std::vector<double> s(m_init);
    double lambda = m_tau * 0.1;

    // make initial;
    if (need_precise) {
        for (int k = 0; k < m_data->sat_setts->simple_iter_count; k++) {
            reset_matrix();

            std::vector<double> as = apply_oper(s, oper_type::a);
            std::vector<double> t1 = cs::common_vector::subtract(m_init, as);
            cs::common_vector::mult_scal(t1, lambda);
            std::vector<double> bs = apply_oper(s, oper_type::b);
            m_rhs = cs::common_vector::add(t1, bs);

            oper(oper_type::b, s);

            s = m_ret.solve(m_rhs);
        }
    }

    // newton
    double eps = 1e-10;
    double err = 10;
    int max_iter = 10;
    int iter = 0;

    // std::vector<double> sf(s);
    while (err > eps && iter < max_iter) {
        reset_matrix();

        std::vector<double> as = apply_oper(s, oper_type::a);
        m_rhs = cs::common_vector::subtract(m_init, as);

        oper(oper_type::ga, s);

        std::vector<double> ksi = m_ret.solve(m_rhs);
        err = cs::common_vector::max_abs(ksi);
        s = cs::common_vector::add(ksi, s);

        // std::cout << "iter=" << iter << ", err = " << err << std::endl;
        iter++;
    }

    return s;
}

void SaturImplicitSolverService::reset_matrix()
{
    int n = m_grd->cells.size();
    m_ret.clear(n);
    m_rhs.assign(n, 0.0);
}

void SaturImplicitSolverService::build_simple()
{
}

void SaturImplicitSolverService::oper(oper_type oper_tp, const std::vector<double>& v)
{
    for (auto& cl : m_grd->cells) {
        m_ret.C[cl->ind] += 1.0;
    }

    double alpha = m_tau / m_data->eps;
    bool is_producer = m_data->is_producer_well();
    for (auto const& fc : m_grd->faces) {
        int upwind_cind = get_cind_s_upwind(fc);
        double un = fc->u * get_face_cf(fc);
        double s = upwind_cind == -1 ? fc->bound_satur : v[upwind_cind];
        double oper_cf = (oper_tp == oper_type::b && upwind_cind != -1)
            ? 1.0
            : get_oper_cf(oper_tp, s, fc->type, is_producer);
        double val = alpha * (un * oper_cf * fc->area);

        if (upwind_cind == -1) {
            double v = val / m_grd->cells[fc->cl1]->volume;
            // if (oper_tp == oper_type::ga) {
            //     m_ret.C[fc->cl1] += v;
            // } else {
            m_rhs[fc->cl1] += v; // un = -un;
            // }
        } else {
            if (upwind_cind == fc->cl2) {
                m_ret.B[fc->cl1] -= val / m_grd->cells[fc->cl1]->volume;
                m_ret.C[fc->cl2] += val / m_grd->cells[fc->cl2]->volume;
            } else {
                if (fc->cl2 != -1) {
                    m_ret.B[fc->cl2] += val / m_grd->cells[fc->cl2]->volume;
                }
                m_ret.C[fc->cl1] -= val / m_grd->cells[fc->cl1]->volume;
            }
        }
    }
}

std::vector<double> SaturImplicitSolverService::apply_oper(const std::vector<double>& v,
    oper_type oper_tp)
{
    std::vector<double> result(m_grd->cells.size(), 0.0);

    double alpha = m_tau / m_data->eps;
    bool is_prod_well = m_data->is_producer_well();
    for (auto& fc : m_grd->faces) {
        int upwind_cind = get_cind_s_upwind(fc);
        double s = upwind_cind == -1 ? fc->bound_satur : v[upwind_cind];
        double oper_cf = get_oper_cf(oper_tp, s, fc->type, is_prod_well);
        double un = fc->u * get_face_cf(fc);
        double val = un * fc->area * oper_cf;

        if (fc->cl2 != -1) {
            result[fc->cl2] += val;
        }
        result[fc->cl1] -= val;
    }

    for (auto& cl : m_grd->cells) {
        result[cl->ind] *= alpha / m_grd->cells[cl->ind]->volume;
        result[cl->ind] += v[cl->ind];
    }

    return result;
}

double SaturImplicitSolverService::get_oper_cf(oper_type oper_tp, double s,
    const mesh::models::FaceType::TypeEnum face_tp, bool is_producer)
{
    switch (oper_tp) {
    case oper_type::a:
        return cs::rp::get_fbl(s, m_data->rp_n, m_data->kmu);
    case oper_type::b:
        return s;
    case oper_type::ga:
        return cs::rp::get_dfbl(s, m_data->rp_n, m_data->kmu);
    default:
        return 0.0;
    }
}

int SaturImplicitSolverService::get_cind_s_upwind(const std::shared_ptr<mesh::models::Face> fc)
{
    return (fc->u > 0.)
        ? fc->cl2
        : fc->cl1;
}

double SaturImplicitSolverService::get_face_cf(const std::shared_ptr<mesh::models::Face> fc)
{
    return mesh::models::FaceType::is_top_bot(fc->type)
        ? 1.0 / (2.0 * m_data->m)
        : 1.0;
}
}
