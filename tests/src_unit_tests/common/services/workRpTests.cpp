
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <memory>

#include "common/models/physData.hpp"
#include "common/services/workRp.hpp"

namespace cs = ble_src::common::services;

namespace tests::unit_tests::common::services::work_rp {

void case1_kw()
{
    // arrange
    double expected = 0.0;
    double s = 0.;
    auto pd = std::make_shared<ble_src::common::models::PhysData>();
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
    auto pd = std::make_shared<ble_src::common::models::PhysData>();
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
    auto pd = std::make_shared<ble_src::common::models::PhysData>();
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
    auto pd = std::make_shared<ble_src::common::models::PhysData>();
    pd->kmu = 0.125; // = mw / moil;
    pd->n_oil = 2.0;
    pd->n_wat = 5.3;

    // act
    double actual = cs::rp::get_koil(s, pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case1_fbl()
{
    // arrange
    double expected = 1.0;
    double s = 1.;
    auto pd = std::make_shared<ble_src::common::models::PhysData>();
    pd->kmu = 0.125; // = mw / moil;
    pd->n_oil = 2.0;
    pd->n_wat = 5.3;

    // act
    double actual = cs::rp::get_fbl(s, pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case2_fbl()
{
    // arrange
    double expected = 0.0;
    double s = 0.;
    auto pd = std::make_shared<ble_src::common::models::PhysData>();
    pd->kmu = 0.125; // = mw / moil;
    pd->n_oil = 2.0;
    pd->n_wat = 5.3;

    // act
    double actual = cs::rp::get_fbl(s, pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case3_fbl()
{
    // arrange
    double expected = 0.2;
    double s = 0.2;
    auto pd = std::make_shared<ble_src::common::models::PhysData>();
    pd->kmu = 1; // = mw / moil;
    pd->n_oil = 1.0;
    pd->n_wat = 1.0;

    // act
    double actual = cs::rp::get_fbl(s, pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case1_sigma()
{
    // arrange
    double expected = 1.0;
    double s = 0.2;
    auto pd = std::make_shared<ble_src::common::models::PhysData>();
    pd->kmu = 1; // = mw / moil;
    pd->n_oil = 1.0;
    pd->n_wat = 1.0;

    // act
    double actual = cs::rp::get_sigma(s, pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case2_sigma()
{
    // arrange
    double expected = 0.1;
    double s = 0.0;
    auto pd = std::make_shared<ble_src::common::models::PhysData>();
    pd->kmu = 0.1; // = mw / moil;
    pd->n_oil = 2.0;
    pd->n_wat = 2.0;

    // act
    double actual = cs::rp::get_sigma(s, pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case1_dfbl()
{
    // arrange
    double expected = 0.0;
    double s = 0.0;
    auto pd = std::make_shared<ble_src::common::models::PhysData>();
    pd->kmu = 0.1; // = mw / moil;
    pd->n_oil = 2.0;
    pd->n_wat = 2.0;

    // act
    double actual = cs::rp::get_dfbl(s, pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case2_dfbl()
{
    // arrange
    double expected = 2.076124567474048; // from wxmaxima
    double s = 0.6;
    auto pd = std::make_shared<ble_src::common::models::PhysData>();
    pd->kmu = 2.0; // = mw / moil;
    pd->n_oil = 2.0;
    pd->n_wat = 2.0;

    // act
    double actual = cs::rp::get_dfbl(s, pd);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

}