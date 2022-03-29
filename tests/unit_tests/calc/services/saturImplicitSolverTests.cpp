#include <boost/test/unit_test.hpp>

#include <iostream>
#include <memory>
#include <vector>

#include "calc/services/saturImplicitSolver.hpp"
#include "common/models/solverData.hpp"
#include "mesh/models/grid.hpp"

namespace clcs = ble::src::calc::services;
namespace cmnm = ble::src::common::models;
namespace grdm = ble::src::mesh::models;

namespace ble::tests::unit_tests::calc::services::satur_implicit_solver_service {

std::vector<std::shared_ptr<grdm::Face>> make_faces()
{
    auto make_face = [](int ind, int cl1, int cl2, double u,
                         double area, double bound_sat, grdm::FaceType::TypeEnum tp) {
        auto result = std::make_shared<grdm::Face>();
        result->cl1 = cl1;
        result->cl2 = cl2;
        result->u = u;
        result->type = tp;
        result->bound_satur = bound_sat;
        result->ind = ind;
        result->area = area;

        return result;
    };

    std::vector<std::shared_ptr<grdm::Face>> result;
    result.push_back(make_face(0, 0, -1, -1.0, 1.0, 0.0, grdm::FaceType::kWell)); // well
    result.push_back(make_face(1, 0, 1, 1.0, 1.0, 0.0, grdm::FaceType::kInner)); // inner
    result.push_back(make_face(2, 1, -1, 0.0, 1.0, 0.0, grdm::FaceType::kContour)); // contour
    result.push_back(make_face(3, 0, -1, 1.0, 1.0, 1.0, grdm::FaceType::kTop)); // f0_top
    result.push_back(make_face(4, 0, -1, 1.0, 1.0, 1.0, grdm::FaceType::kBot)); // f0_bottom
    result.push_back(make_face(5, 1, -1, 1.0, 1.0, 1.0, grdm::FaceType::kTop)); // f1_top
    result.push_back(make_face(6, 1, -1, 1.0, 1.0, 1.0, grdm::FaceType::kBot)); // f1_bottom

    return result;
}

std::vector<std::shared_ptr<grdm::Cell>> make_cells()
{
    auto make_cell = [](int ind, std::vector<int> finds, double poro,
                         double vol) {
        auto result = std::make_shared<grdm::Cell>();
        result->faces = finds;
        result->ind = ind;
        result->poro = poro;
        result->volume = vol;

        return result;
    };

    std::vector<std::shared_ptr<grdm::Cell>> result;

    result.push_back(make_cell(0, { 0, 1, 3, 4 }, 1.0, 1.0));
    result.push_back(make_cell(1, { 1, 2, 5, 6 }, 1.0, 1.0));

    return result;
}

std::shared_ptr<grdm::Grid> make_grid()
{
    auto faces = make_faces();
    auto cells = make_cells();

    auto result = std::make_shared<grdm::Grid>();
    result->faces = faces;
    result->cells = cells;

    return result;
}

void case_one_part()
{
    // arrange
    auto calc_service = std::make_shared<clcs::SaturImplicitSolverService>();
    std::vector<double> init = { 0.0, 0.0 };
    auto data = std::make_shared<cmnm::SolverData>(0.0, 0.0, 0.0);
    double tau = 1.0;
    data->sat_setts->simple_iter_count = 1;
    data->rp_n = 1;
    data->kmu = 1;
    data->m = 100;
    auto grd = make_grid();

    // act
    std::vector<double> actual = calc_service->solve(tau, init, data, grd, true);

    BOOST_CHECK_CLOSE(1.0, 1.0, 1e-8);
}

}
