#ifndef BLE_SRC_SATURIMPLICITSOLVERSERVICE_H_
#define BLE_SRC_SATURIMPLICITSOLVERSERVICE_H_

#include "calc/models/diagMatrix.hpp"
#include "common/models/solverData.hpp"
#include "mesh/models/grid.hpp"

namespace ble::src::calc::services {

class SaturImplicitSolverService {
public:
    SaturImplicitSolverService() { }
    ~SaturImplicitSolverService() { }
    std::vector<double> solve(double tau, const std::vector<double>& init,
        const std::shared_ptr<common::models::SolverData> data,
        const std::shared_ptr<mesh::models::Grid> grd, bool need_precise);

private:
    enum oper_type {
        a,
        b,
        ga
    };
    std::shared_ptr<common::models::SolverData> m_data;
    std::shared_ptr<mesh::models::Grid> m_grd;
    std::vector<double> m_rhs;
    int m_simple_count;
    double m_tau;
    std::vector<double> m_init;
    models::DiagMat m_ret;

    void build_simple();
    void oper(oper_type oper_tp, const std::vector<double>& v);

    std::vector<double> apply_oper(const std::vector<double>& v, oper_type oper_tp);
    double get_face_cf(const std::shared_ptr<mesh::models::Face> fc);
    double get_oper_cf(oper_type oper_tp, double s);
    int get_cind_s_upwind(const std::shared_ptr<mesh::models::Face> fc);
    void reset_matrix();
};
}

#endif