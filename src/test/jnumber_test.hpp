#ifndef JNUMBER_TEST_H
#define JNUMBER_TEST_H

#include "catch.hpp"
#include "../main/include/jnumber.h"

#include <limits>
#include <string>

using namespace std;
using namespace yson;

TEST_CASE( "is include guard macro in jnumber.h implemented", "[jnumber]" ) {
    #ifdef JNUMBER_H
        REQUIRE(true);
    #else
        INFO("include guard macro JNUMBER_H not implemented");
        REQUIRE(false);
    #endif
}

void testJNumberWithValue(const int64_t testValue, string excpected) {
    JNumber jnumber;
    jnumber.setSinged(testValue);

    REQUIRE(jnumber.toString() ==  excpected);
    REQUIRE(jnumber.getSinged() ==  testValue);
}

TEST_CASE( "create JNumber with max int64_t value", "[jnumber]" ) {
    testJNumberWithValue(numeric_limits<int64_t>::max(), "9223372036854775807");
}

TEST_CASE( "create JNumber with min int64_t value", "[jnumber]" ) {
    testJNumberWithValue(numeric_limits<int64_t>::min(), "-9223372036854775808");
}

void testJNumberWithUnsigned4Value(const uint64_t testValue, const string excpected) {
    JNumber jnumber;
    jnumber.setUnsigned(testValue);

    REQUIRE(jnumber.toString() ==  excpected);
    REQUIRE(jnumber.getUnsinged() ==  testValue);
}

TEST_CASE( "create JNumber with max unsigned value", "[jnumber]" ) {
    testJNumberWithUnsigned4Value(numeric_limits<uint64_t>::max(), "18446744073709551615");
}

TEST_CASE( "create JNumber with min unsigned value", "[jnumber]" ) {
    testJNumberWithUnsigned4Value(0, "0");
}

void testJNumberWithFloatingValue(const double testValue, const string expected) {
    JNumber jnumber;
    jnumber.setFloating(testValue);
    
    REQUIRE(jnumber.toString() ==  expected);
    REQUIRE(jnumber.getFloating() ==  testValue);
}

// TEST_CASE( "create JNumber with max floating value", "[jnumber]" ) {
//    testJNumberWithFloatingValue(numeric_limits<double>::max(), "1.79769e+308");
//}

//TEST_CASE( "create JNumber with min floating value", "[jnumber]" ) {
//    testJNumberWithFloatingValue(numeric_limits<double>::min(), "2.22507e-308");
//}

//TEST_CASE( "create JNumber with floating value", "[jnumber]" ) {
//    testJNumberWithFloatingValue(-4.0987654321, "-4.0987654321");
//}

TEST_CASE( "create JNumber with floating value", "[jnumber]" ) {
    testJNumberWithFloatingValue(-4.0987654321, "-4.098765");
}


#endif