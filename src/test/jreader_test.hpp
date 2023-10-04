#ifndef JREADER_TEST_H
#define JREADER_TEST_H

#include <memory>

#include "catch.hpp"
#include "../main/include/jreader.h"

using namespace std;
using namespace yson;

TEST_CASE( "is include guard macro in jreader.h implemented", "[jreader]" ) {
    #ifdef JREADER_TEST_H
        REQUIRE(true);
    #else
        INFO("include guard macro JREADER_H not implemented");
        REQUIRE(false);
    #endif
}

TEST_CASE( "create JReader and parse JSON string", "[jreader]" ) {
    JReader jreader;
    JDocument jdocumet = jreader.parse("{ \"myNumber\": 42 }");

    shared_ptr<JObject> jvalue = dynamic_pointer_cast<JObject>(jdocumet.getRoot());

    REQUIRE(jvalue->getNumber("myNumber")->getUnsinged() == 42);
}

#endif