#include <boost/test/included/unit_test.hpp>
using namespace boost::unit_test;

#include "src_unit_tests/common/services/shockFrontTests.hpp"
#include "src_unit_tests/common/services/workRpTests.hpp"

test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
    test_suite* ts_shock_front = BOOST_TEST_SUITE("ShockFrontTests");
    ts_shock_front->add(BOOST_TEST_CASE(&tests::unit_tests::common::services::shock_front::case1));
    ts_shock_front->add(BOOST_TEST_CASE(&tests::unit_tests::common::services::shock_front::case2));

    test_suite* ts_work_rp = BOOST_TEST_SUITE("WorkRpTests");
    ts_work_rp->add(BOOST_TEST_CASE(&tests::unit_tests::common::services::work_rp::case1_kw));
    ts_work_rp->add(BOOST_TEST_CASE(&tests::unit_tests::common::services::work_rp::case2_kw));
    ts_work_rp->add(BOOST_TEST_CASE(&tests::unit_tests::common::services::work_rp::case1_koil));    
    ts_work_rp->add(BOOST_TEST_CASE(&tests::unit_tests::common::services::work_rp::case2_koil));
    ts_work_rp->add(BOOST_TEST_CASE(&tests::unit_tests::common::services::work_rp::case1_fbl));
    ts_work_rp->add(BOOST_TEST_CASE(&tests::unit_tests::common::services::work_rp::case2_fbl));
    ts_work_rp->add(BOOST_TEST_CASE(&tests::unit_tests::common::services::work_rp::case3_fbl));
    ts_work_rp->add(BOOST_TEST_CASE(&tests::unit_tests::common::services::work_rp::case1_sigma));
    ts_work_rp->add(BOOST_TEST_CASE(&tests::unit_tests::common::services::work_rp::case2_sigma));
    ts_work_rp->add(BOOST_TEST_CASE(&tests::unit_tests::common::services::work_rp::case1_dfbl));
    ts_work_rp->add(BOOST_TEST_CASE(&tests::unit_tests::common::services::work_rp::case2_dfbl));

    framework::master_test_suite().add(ts_shock_front);
    framework::master_test_suite().add(ts_work_rp);

    return 0;
}
