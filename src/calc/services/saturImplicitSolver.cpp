#include "saturImplicitSolver.hpp"

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

std::vector<double> SaturImplicitSolverService::solve(const std::vector<double>& init,
    const std::shared_ptr<common::models::SolverData> data,
    const std::shared_ptr<mesh::models::Grid> grd, bool need_precise)
{
    m_data = data;
    m_init = init;
    m_grd = grd;

    m_ret.resize(grd->cells.size());
    m_rhs.resize(grd->cells.size(), 0.0);

    // std::vector<double> new_s;
    std::vector<double> s(m_init);
    double lambda = 0.1;

    // make initial;
    if (need_precise) {
        for (int k = 0; k < m_data->sat_setts->simple_iter_count; k++) {
            std::vector<double> as = apply_oper(s, oper_type::a);
            std::vector<double> t1 = cs::common_vector::subtract(s, as);
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
    int max_iter = 50;
    int iter = 0;
    while (err > eps || iter < max_iter) {
        std::vector<double> as = apply_oper(s, oper_type::a);
        std::vector<double> t1 = cs::common_vector::subtract(s, as);
        m_rhs = cs::common_vector::subtract(t1, as);

        oper(oper_type::ga, s);

        std::vector<double> ksi = m_ret.solve(m_rhs);
        err = cs::common_vector::max_abs(ksi);
        s = cs::common_vector::add(ksi, s);
    }

    return init;
}

void SaturImplicitSolverService::build_simple()
{
}

void SaturImplicitSolverService::oper(oper_type oper_tp, const std::vector<double>& v)
{
    double poro = 1.0;
    double alpha = m_data->sat_setts->tau / poro;
    for (auto& fc : m_grd->faces) {
        int upwind_cind = get_cind_s_upwind(fc);
        double s = oper_tp == oper_type::b
            ? 1.0
            : upwind_cind == -1
            ? fc->bound_satur
            : v[upwind_cind];
        double oper_cf = get_oper_cf(oper_tp, s);
        double cf = get_cf(fc);
        double val = fc->u * fc->area * cf * oper_cf;
        double vol1 = m_grd->cells[fc->cl1]->volume;
        if (upwind_cind == -1) {
            m_rhs[fc->cl1] -= val * (alpha / vol1);
        } else {
            double vol2 = m_grd->cells[fc->cl2]->volume;
            if (upwind_cind == fc->cl2) {
                m_ret.B[fc->cl1] += val * (alpha / vol1);
                m_ret.C[fc->cl2] += val * (alpha / vol2);
            } else {
                m_ret.B[fc->cl2] += val * (alpha / vol2);
                m_ret.C[fc->cl1] += val * (alpha / vol1);
            }
        }
    }

    for (auto& cl : m_grd->cells) {
        m_ret.C[cl->ind] += 1.0;
    }
}

std::vector<double> SaturImplicitSolverService::apply_oper(const std::vector<double>& v, oper_type oper_tp)
{
    std::vector<double> result(m_grd->cells.size(), 0.0);

    double poro = 1.0;
    double alpha = m_data->sat_setts->tau / poro;
    for (auto& fc : m_grd->faces) {
        int upwind_cind = get_cind_s_upwind(fc);
        double s = upwind_cind == -1
            ? fc->bound_satur
            : v[upwind_cind];
        double oper_cf = get_oper_cf(oper_tp, s);
        double cf = get_cf(fc);
        double val = oper_cf * fc->u * fc->area * cf;
        double vol1 = m_grd->cells[fc->cl1]->volume;
        if (upwind_cind != -1) {
            double vol2 = m_grd->cells[fc->cl2]->volume;
            if (upwind_cind == fc->cl2) {
                result[fc->cl2] += val * (alpha / vol2);
            } else {
                result[fc->cl1] += val * (alpha / vol1);
            }
        }
    }

    for (auto& cl : m_grd->cells) {
        result[cl->ind] += v[cl->ind];
    }

    return result;
}

double SaturImplicitSolverService::get_oper_cf(oper_type oper_tp, double s)
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

double SaturImplicitSolverService::get_cf(const std::shared_ptr<mesh::models::Face> fc)
{
    return mesh::models::FaceType::is_top_bot(fc->type)
        ? 1.0 / (2.0 * m_data->m)
        : 1.0;
}

}
