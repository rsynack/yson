#ifndef JNULL_TEST_H
#define JNULL_TEST_H

#include "catch.hpp"
#include "../main/include/jnull.h"

using namespace yson;

TEST_CASE( "is include guard macro in jnull.h implemented", "[jnull]" ) {
    #ifdef JNULL_H
        REQUIRE(true);
    #else
        INFO("include guard macro JNULL_H not implemented");
        REQUIRE(false);
    #endif
}

TEST_CASE( "create JNull value", "[jnull]" ) {
    JNull jnull;
    REQUIRE(jnull.toString() == "null");
}

#endif