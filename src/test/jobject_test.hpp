#ifndef JOBJECT_TEST_H
#define JOBJECT_TEST_H

#include "catch.hpp"
#include "../main/include/jobject.h"

#include <string>

using namespace std;
using namespace yson;

const string JOBJECT_TEST_TAG = "[jobject]";

TEST_CASE( "is include guard macro in jobject.h implemented", JOBJECT_TEST_TAG) {
    #ifdef JOBJECT_H
        REQUIRE(true);
    #else
        INFO("include guard macro JOBJECT_H not implemented");
        REQUIRE(false);
    #endif
}

TEST_CASE( "create empty JObject value", JOBJECT_TEST_TAG) {
    JObject jobject;

    REQUIRE(jobject.toString() == "{ }");
}

JObject createJObject() {
    JObject jobject;

    jobject.addBoolean("myBoolean", true);
    jobject.addNumber("myNumber", (int64_t)42);
    jobject.addString("myString", "Hello World!");

    JNull jnull;
    jobject.addValue("myNullValue", jnull);

    return jobject;
}

string getExcpectedValue() {
    return "{ \"myBoolean\": true, \"myNumber\": 42, \"myString\": \"Hello World!\", \"myNullValue\": null }";
}

TEST_CASE( "create JObject with properties", JOBJECT_TEST_TAG) {
    JObject jobject = createJObject();

    REQUIRE(jobject.toString() == getExcpectedValue());
}

TEST_CASE( "create JObject with embedded object", JOBJECT_TEST_TAG) {
    JObject jobject;

    JObject embeddedObject = createJObject();

    jobject.addValue("myObject", embeddedObject);

    REQUIRE(jobject.toString() == "{ \"myObject\": " + getExcpectedValue() + " }");
}

TEST_CASE( "create JObject with array", JOBJECT_TEST_TAG) {
    JObject jobject;

    JArray array;
    array.addString("Hello");
    array.addString("World");
    array.addString("!");

    jobject.addValue("myArray", array);

    REQUIRE(jobject.toString() == "{ \"myArray\": [\"Hello\", \"World\", \"!\"] }");
}

#endif