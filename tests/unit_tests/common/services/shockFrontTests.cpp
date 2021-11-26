// #define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE ShockFrontTests
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <memory>

#include "common/services/shockFront.hpp"

namespace cs = ble::src::common::services;

namespace ble::tests::unit_tests::common::services::shock_front {

void case1()
{
    // arrange
    double expected = 0.33355000000000001;
    double kmu = 0.125; // = mw / moil;
    double n = 2.0;

    // act
    double actual = cs::shock_front::get_shock_front(n, kmu);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case2()
{
    // arrange
    double expected = 0.8163999999999999; // wxmaxima gives 0.8164965809277261;
    double kmu = 2.0; // = mw / moil;
    double n = 2.0;

    // act
    double actual = cs::shock_front::get_shock_front(n, kmu);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

}