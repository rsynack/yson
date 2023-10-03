#ifndef JDATE_TEST_H
#define JDATE_TEST_H

#include <ctime>

#include "catch.hpp"
#include "../main/include/jdate.h"

using namespace std;
using namespace yson;

TEST_CASE( "is include guard macro in jdate.h implemented", "[jdate]" ) {
    #ifdef JDATE_H
        REQUIRE(true);
    #else
        INFO("include guard macro JDATE_H not implemented");
        REQUIRE(false);
    #endif
}

TEST_CASE( "create JDate value", "[jdate]" ) {

    std::tm tm{};
    tm.tm_year = 2023-1900;
    tm.tm_mday = 5;
    tm.tm_mon = 8;
    tm.tm_hour = 20;
    tm.tm_min = 5;
    tm.tm_sec = 14;

    time_t time = mktime(&tm);// + (456/1000);

    JDate date(time);

    REQUIRE(date.toString() == "2023-09-05T19:05:14Z");
}

#endif