#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BleTests
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(BleCommonTests)

BOOST_AUTO_TEST_CASE(TestFbl)
{
	// arrange 
	double expected = 1.;

	// act
	double actual = 1.;

	// assert
	BOOST_CHECK_CLOSE(expected, actual, 1e-8);
}

BOOST_AUTO_TEST_SUITE_END()
