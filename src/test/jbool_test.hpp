#ifndef JBOOL_TEST_H
#define JBOOL_TEST_H

#include "catch.hpp"
#include "../main/include/jbool.h"

using namespace yson;

TEST_CASE( "is include guard macro in jbool.h implemented", "[jbool]" ) {
    #ifdef JBOOL_H
        REQUIRE(true);
    #else
        INFO("include guard macro JBOOL_H not implemented");
        REQUIRE(false);
    #endif
}

TEST_CASE( "create JBool with true value", "[jbool]" ) {
    JBool jbool(true);

    REQUIRE(jbool.toString() == "true");
    REQUIRE(jbool.getValue());
}

TEST_CASE( "create JBool with false value", "[jbool]" ) {
    JBool jbool(false);

    REQUIRE(jbool.toString() == "false");
    REQUIRE(!jbool.getValue());
}

#endif