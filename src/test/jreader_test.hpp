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

TEST_CASE( "create JReader and parse JSON string to object", "[jreader]" ) {
    JReader jreader;
    JDocument jdocumet = jreader.parse("{ \"myNumber\": 42 }");

    shared_ptr<JObject> root = jdocumet.getRoot<JObject>();
    shared_ptr<JObject> object = jdocumet.getObject();

    REQUIRE(root->getNumber("myNumber")->getUnsinged() == 42);
    REQUIRE(object->getNumber("myNumber")->getUnsinged() == 42);

    REQUIRE_THROWS_WITH(jdocumet.getArray(), "Invalid root node type 'JArray'.");
}

TEST_CASE( "create JReader and parse JSON string to array", "[jreader]" ) {
    JReader jreader;
    JDocument jdocumet = jreader.parse("[33, 42, 78]");

    shared_ptr<JArray> root = jdocumet.getRoot<JArray>();
    shared_ptr<JArray> array = jdocumet.getArray();

    //REQUIRE(root[1] == 42);
    //REQUIRE(object[3]== 42);

    REQUIRE_THROWS_WITH(jdocumet.getObject(), "Invalid root node type 'JObject'.");
}

TEST_CASE( "create JReader and parse JSON without root node", "[jreader]" ) {
    JReader jreader;

    REQUIRE_THROWS_WITH(jreader.parse("\"test\": 23, \"test2\": true"), "Root not found in JSON.");
}

#endif