#include <boost/test/unit_test.hpp>

#include <iostream>
#include <memory>
#include <vector>

#include "common/models/dataDistribution.hpp"
#include "common/services/dataDistributionService.hpp"

namespace cs = ble::src::common::services;

namespace ble::tests::unit_tests::common::services::bound_source_service {

void case_one_part()
{
    std::string file_name = "../../samples/rhs/const.blerhs";
    auto expected = std::make_shared<src::common::models::DataDistribution>();
    expected->x0 = 0.0;
    expected->x1 = 100.0;
    expected->v0 = 0.01;
    expected->v1 = 0.01;

    // act
    auto v = cs::DataDistributionService::get_data_from_file(file_name);
    auto actual = v[0];

    // assert
    BOOST_CHECK_CLOSE(expected->x0, actual->x0, 1e-8);
    BOOST_CHECK_CLOSE(expected->x1, actual->x1, 1e-8);
    BOOST_CHECK_CLOSE(expected->v0, actual->v0, 1e-8);
    BOOST_CHECK_CLOSE(expected->v1, actual->v1, 1e-8);
}

void case_two_part()
{
    std::string file_name = "../../samples/rhs/const_two_part.blerhs";
    auto expected = 2;
    double x1_0 = 0.5;
    double x1_1 = 1.0;

    // act
    auto v = cs::DataDistributionService::get_data_from_file(file_name);

    // assert
    BOOST_CHECK_EQUAL(expected, v.size());
    BOOST_CHECK_CLOSE(x1_0, v[0]->x1, 1e-8);
    BOOST_CHECK_CLOSE(x1_1, v[1]->x1, 1e-8);
}

void case_two_part_bad()
{
    std::string file_name = "../../samples/rhs/const_two_part_bad.blerhs";

    // act
    auto v = cs::DataDistributionService::get_data_from_file(file_name);

    // assert
    BOOST_CHECK_EQUAL(0, v.size());
}

}