// #define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE ShockFrontTests
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <memory>

#include "common/services/shockFront.hpp"
#include "common/models/physData.hpp"

namespace cs = ble::src::common::services;

namespace ble::tests::unit_tests::common::services::shock_front {

void case1()
{
    // arrange
    double expected = 0.66564999999999996;
    auto pd = std::make_shared<ble::src::common::models::PhysData>();
    pd->kmu = 0.125; // = mw / moil;
    pd->n_oil = 2.0;
    pd->n_wat = 5.3;

    // act
    double actual = cs::shock_front::get_shock_front(pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case2()
{
    // arrange
    double expected = 0.8163999999999999; // wxmaxima gives 0.8164965809277261;
    auto pd = std::make_shared<src::common::models::PhysData>();
    pd->kmu = 2.0; // = mw / moil;
    pd->n_oil = 2.0;
    pd->n_wat = 2.0;

    // act
    double actual = cs::shock_front::get_shock_front(pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

}