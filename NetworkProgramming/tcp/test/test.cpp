//
// Created by shea on 1/6/22.
//
#include <vector>
#define BOOST_TEST_MODULE example_test_suite
#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_CASE(add_example)
{
    auto integers = {1, 2, 3, 4, 5};
    auto result = (integers);
    BOOST_REQUIRE(result == 15);
}