
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <memory>

#include "common/services/workRp.hpp"

namespace cs = ble::src::common::services;

namespace ble::tests::unit_tests::common::services::work_rp {

void case1_kw()
{
    // arrange
    double expected = 0.0;
    double s = 0.;
    double n = 2.0;

    // act
    double actual = cs::rp::get_kw(s, n);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case2_kw()
{
    // arrange
    double expected = 1.0;
    double s = 1.;
    double n = 2.0;

    // act
    double actual = cs::rp::get_kw(s, n);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case1_koil()
{
    // arrange
    double expected = 1.0;
    double s = 0.;
    double n = 2.0;

    // act
    double actual = cs::rp::get_koil(s, n);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case2_koil()
{
    // arrange
    double expected = 0.0;
    double s = 1.;
    double n = 2.0;

    // act
    double actual = cs::rp::get_koil(s, n);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case1_fbl()
{
    // arrange
    double expected = 1.0;
    double s = 1.;
    double kmu = 0.125; // = mw / moil;
    double n = 2.0;

    // act
    double actual = cs::rp::get_fbl(s, n, kmu);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case2_fbl()
{
    // arrange
    double expected = 0.0;
    double s = 0.;
    double kmu = 0.125; // = mw / moil;
    double n = 2.0;

    // act
    double actual = cs::rp::get_fbl(s, n, kmu);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case3_fbl()
{
    // arrange
    double expected = 0.2;
    double s = 0.2;
    double kmu = 1.0; // = mw / moil;
    double n = 1.0;

    // act
    double actual = cs::rp::get_fbl(s, n, kmu);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case1_sigma()
{
    // arrange
    double expected = 1.0;
    double s = 0.2;
    double kmu = 1.0; // = mw / moil;
    double n = 1.0;

    // act
    double actual = cs::rp::get_sigma(s, n, kmu);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case2_sigma()
{
    // arrange
    double expected = 0.1;
    double s = 0.0;
    double kmu = 0.1; // = mw / moil;
    double n = 2.0;

    // act
    double actual = cs::rp::get_sigma(s, n, kmu);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case1_dfbl()
{
    // arrange
    double expected = 0.0;
    double s = 0.0;
    double kmu = 0.1; // = mw / moil;
    double n = 2.0;

    // act
    double actual = cs::rp::get_dfbl(s, n, kmu);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case2_dfbl()
{
    // arrange
    double expected = 2.076124567474048; // from wxmaxima
    double s = 0.6;
    double kmu = 2.0; // = mw / moil;
    double n = 2.0;

    // act
    double actual = cs::rp::get_dfbl(s, n, kmu);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case1_dfbl_approx()
{
    // arrange
    double d = 0.01;
    double expected = 0.020401917780266121; // from wxmaxima
    double s = 1.0;
    double kmu = 2.0; // = mw / moil;
    double n = 2.0;

    // act
    double actual = cs::rp::get_dfbl_approx(s, n, kmu, false, d);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case2_dfbl_approx()
{
    // arrange
    double d = 0.1;
    double expected = 0.24096385542168641; // from wxmaxima
    double s = 1.0;
    double kmu = 2.0; // = mw / moil;
    double n = 2.0;

    // act
    double actual = cs::rp::get_dfbl_approx(s, n, kmu, false, d);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

void case3_dfbl_approx()
{
    // arrange
    double d = 0.1;
    double expected = 0.06134969325153374; // from wxmaxima
    double s = 0.0;
    double kmu = 2.0; // = mw / moil;
    double n = 2.0;

    // act
    double actual = cs::rp::get_dfbl_approx(s, n, kmu, true, d);

    // assert
    BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

}