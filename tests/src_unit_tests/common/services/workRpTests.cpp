// #define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE WorkRpTests
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <memory>

#include "common/services/workRp.hpp"
#include "physData.hpp"

namespace cs = ble_src::common::services;

namespace tests::unit_tests::common::services::work_rp {

void case1_kw()
{
    // arrange
    double expected = 0.0;
    double s = 0.;
    auto pd = std::make_shared<ble_src::PhysData>();
    pd->kmu = 0.125; // = mw / moil;
    pd->n_oil = 2.0;
    pd->n_wat = 5.3;

    // act
    double actual = cs::rp::get_kw(s, pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case2_kw()
{
    // arrange
    double expected = 1.0;
    double s = 1.;
    auto pd = std::make_shared<ble_src::PhysData>();
    pd->kmu = 0.125; // = mw / moil;
    pd->n_oil = 2.0;
    pd->n_wat = 5.3;

    // act
    double actual = cs::rp::get_kw(s, pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case1_koil()
{
    // arrange
    double expected = 1.0;
    double s = 0.;
    auto pd = std::make_shared<ble_src::PhysData>();
    pd->kmu = 0.125; // = mw / moil;
    pd->n_oil = 2.0;
    pd->n_wat = 5.3;

    // act
    double actual = cs::rp::get_koil(s, pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case2_koil()
{
    // arrange
    double expected = 0.0;
    double s = 1.;
    auto pd = std::make_shared<ble_src::PhysData>();
    pd->kmu = 0.125; // = mw / moil;
    pd->n_oil = 2.0;
    pd->n_wat = 5.3;

    // act
    double actual = cs::rp::get_koil(s, pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

}