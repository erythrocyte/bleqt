// #define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE ShockFrontTests
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <memory>

#include "common/services/shockFront.hpp"
#include "common/models/physData.hpp"

namespace cs = ble_src::common::services;

namespace tests::unit_tests::common::services::shock_front {

void case1()
{
    // arrange
    double expected = 0.66559999999999997;
    auto pd = std::make_shared<ble_src::common::models::PhysData>();
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
    double expected = 0.81679999999; // wxmaxima gives 0.8164965809277261;
    auto pd = std::make_shared<ble_src::common::models::PhysData>();
    pd->kmu = 2.0; // = mw / moil;
    pd->n_oil = 2.0;
    pd->n_wat = 2.0;

    // act
    double actual = cs::shock_front::get_shock_front(pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

}