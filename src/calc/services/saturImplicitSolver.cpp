#include "saturImplicitSolver.hpp"

#include <cmath>

#include "common/services/commonVector.hpp"
#include "common/services/workRp.hpp"
#include "mesh/models/faceType.hpp"

namespace cs = ble::src::common::services;

namespace ble::src::calc::services {

// SaturImplicitSolverService::SaturImplicitSolverService( //const std::shared_ptr<common::models::SolverData> data,
//     const std::shared_ptr<mesh::models::Grid> grd)
// {
//     // m_data = data;
//     m_grd = grd;
// }

// SaturImplicitSolverService::~SaturImplicitSolverService()
// {
// }

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
            // else if (ri == n - 1) {
            //     std::cout << "(" << 0 << "\t" << mtr.C[ri] << ") * () = (" << rhs[ri] << ")" << std::endl;
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
    double lambda = 0.01;

    // make initial;
    if (need_precise) {
        for (int k = 0; k < m_data->sat_setts->simple_iter_count; k++) {
            reset_matrix();

            std::vector<double> as = apply_oper(s, oper_type::a);
            // print_vector(as, "As", "simple b");
            std::vector<double> t1 = cs::common_vector::subtract(m_init, as);
            // std::vector<double> t1 = cs::common_vector::subtract(s, as);
            cs::common_vector::mult_scal(t1, lambda);
            std::vector<double> bs = apply_oper(s, oper_type::b);
            m_rhs = cs::common_vector::add(t1, bs);
            // print_vector(m_rhs, "r", "simble b");

            oper(oper_type::b, s);
            // print_system(m_ret, m_rhs);
            // print_vector(m_rhs, "r(aft)", "simble b");

            s = m_ret.solve(m_rhs);
            // print_vector(s, "s", "simple b");
        }
    }

    // cs::common_vector::save_vector("simple_b_s.dat", s);

    // print_vector(s, "s", "simple b");

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
        // m_rhs = cs::common_vector::subtract(s, as);
        // print_vector(m_rhs, "r", "newton");

        oper(oper_type::ga, s);
        // print_system(m_ret, m_rhs);
        // print_vector(m_rhs, "r(aft)", "newton");

        std::vector<double> ksi = m_ret.solve(m_rhs);
        err = cs::common_vector::max_abs(ksi);
        s = cs::common_vector::add(ksi, s);
        // print_vector(s, "s", "newton");

        std::cout << "iter=" << iter << ", err = " << err << std::endl;
        iter++;
    }

    return s;
}

void SaturImplicitSolverService::reset_matrix()
{
    m_ret.resize(m_grd->cells.size());
    m_rhs.resize(m_grd->cells.size(), 0.0);
}

void SaturImplicitSolverService::build_simple()
{
}

void SaturImplicitSolverService::oper(oper_type oper_tp, const std::vector<double>& v)
{
    double poro = 1.0;
    // double alpha = m_tau / poro;
    // for (auto& fc : m_grd->faces) {
    //     int upwind_cind = get_cind_s_upwind(fc);
    //     double s = upwind_cind == -1
    //         ? fc->bound_satur
    //         : v[upwind_cind];
    //     double oper_cf = (oper_tp == oper_type::b && upwind_cind != -1)
    //         ? 1.0
    //         : get_oper_cf(oper_tp, s);
    //     double un = fc->u * get_face_cf(fc);
    //     double val = (un * fc->area * oper_cf) * alpha;
    //     double vol1 = m_grd->cells[fc->cl1]->volume;
    //     if (upwind_cind == -1) {
    //         m_rhs[fc->cl1] += val / vol1; // un = -un;
    //     } else {
    //         if (upwind_cind == fc->cl2) { // un = -un;
    //             m_ret.B[fc->cl1] -= val / vol1;
    //             m_ret.C[fc->cl2] += val / m_grd->cells[fc->cl2]->volume;
    //         } else {
    //             if (fc->cl2 != -1)
    //                 m_ret.B[fc->cl2] -= val * m_grd->cells[fc->cl2]->volume;
    //             m_ret.C[fc->cl1] += val * vol1;
    //         }
    //     }
    // }

    // for (auto& cl : m_grd->cells) {
    //     m_ret.C[cl->ind] += 1.0;
    // }

    for (auto const& cl : m_grd->cells) {
        double alpha = m_tau / (poro * cl->volume);

        m_ret.C[cl->ind] = 1.0;
        for (auto& fi : cl->faces) {
            auto fc = m_grd->faces[fi];
            int upwind_cind = get_cind_s_upwind(fc);
            // if (upwind_cind == -1)
            //     continue;
            double u = (fc->cl1 == cl->ind) ? -fc->u : fc->u;
            double un = u * get_face_cf(fc);
            double s = upwind_cind == -1 ? fc->bound_satur : v[upwind_cind];
            double oper_cf = (oper_tp == oper_type::b && upwind_cind != -1)
                ? 1.0
                : get_oper_cf(oper_tp, s, v[fc->cl1], upwind_cind == -1);
            double val = alpha * (un * oper_cf * fc->area);

            if (upwind_cind == -1) {
                // if (oper_tp == oper_type::ga)
                //     m_rhs[cl->ind] -= val * s;
                // else
                m_rhs[cl->ind] -= val; // un = -un;
            } else {
                if (upwind_cind != cl->ind) { // un = -un;
                    m_ret.B[cl->ind] += val;
                } else {
                    m_ret.C[cl->ind] += val;
                }
            }
        }
    }
}

std::vector<double> SaturImplicitSolverService::apply_oper(const std::vector<double>& v,
    oper_type oper_tp)
{
    std::vector<double> result(m_grd->cells.size(), 0.0);

    double poro = 1.0;
    // double alpha = m_tau / poro;
    // for (auto& fc : m_grd->faces) {
    //     int upwind_cind = get_cind_s_upwind(fc);
    //     double s = upwind_cind == -1
    //         ? fc->bound_satur
    //         : v[upwind_cind];
    //     double oper_cf = get_oper_cf(oper_tp, s);
    //     double un = fc->u * get_face_cf(fc);
    //     double val = un * fc->area * oper_cf;
    //     double vol1 = m_grd->cells[fc->cl1]->volume;
    //     if (upwind_cind != -1) {
    //         if (upwind_cind == fc->cl2) {
    //             double vol2 = m_grd->cells[fc->cl2]->volume;
    //             result[fc->cl2] -= val * (alpha / vol2);
    //         } else {
    //             result[fc->cl1] += val * (alpha / vol1);
    //         }
    //     }
    // }

    // for (auto& cl : m_grd->cells) {
    //     result[cl->ind] += v[cl->ind];
    // }

    for (auto const& cl : m_grd->cells) {
        double alpha = m_tau / (poro * cl->volume);
        result[cl->ind] = v[cl->ind];
        for (auto& fi : cl->faces) {
            auto fc = m_grd->faces[fi];
            int upwind_cind = get_cind_s_upwind(fc);
            if (upwind_cind == -1)
                continue;
            double u = (fc->cl1 == cl->ind) ? -fc->u : fc->u;
            double un = u * get_face_cf(fc);
            double s = upwind_cind == -1 ? fc->bound_satur : v[upwind_cind];
            double oper_cf = get_oper_cf(oper_tp, s, v[fc->cl1], upwind_cind == -1);
            double val = alpha * (un * oper_cf * fc->area);

            result[cl->ind] += val;
        }
    }

    return result;
}

double SaturImplicitSolverService::get_oper_cf(oper_type oper_tp, double s, double s2, bool calc_aver)
{
    switch (oper_tp) {
    case oper_type::a:
        return cs::rp::get_fbl(s, m_data->rp_n, m_data->kmu);
    case oper_type::b:
        return s;
    case oper_type::ga:
        return calc_aver
            //     ? std::max(
            //         std::max(
            //             cs::rp::get_dfbl(s, m_data->rp_n, m_data->kmu),
            //             cs::rp::get_dfbl(s2, m_data->rp_n, m_data->kmu)),
            //         cs::rp::get_dfbl((s + s2) * 0.5, m_data->rp_n, m_data->kmu))
            ? 1.0
            : cs::rp::get_dfbl(s, m_data->rp_n, m_data->kmu);
        // return cs::rp::get_dfbl(s, m_data->rp_n, m_data->kmu);
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
