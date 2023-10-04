#ifndef JSTRING_TEST_H
#define JSTRING_TEST_H

#include "catch.hpp"
#include "../main/include/jstring.h"

#include <string>

using namespace std;
using namespace yson;

const string JSTRING_TEST_TAG = "[jstring]";

TEST_CASE( "is include guard macro in jstring.h implemented", JSTRING_TEST_TAG) {
    #ifdef JSTRING_H
        REQUIRE(true);
    #else
        INFO("include guard macro JSTRING_H not implemented");
        REQUIRE(false);
    #endif
}

string createExpectedValue(string testValue) {
    string resultValue("\"");
    resultValue.append(testValue);
    resultValue.append("\"");

    return resultValue;
}

TEST_CASE( "create JString string value", JSTRING_TEST_TAG ) {
    const string testValue = "teststr";
    JString jstring(testValue);
    
    string expectedValue = createExpectedValue(testValue);

    REQUIRE(jstring.toString() ==  expectedValue);
    REQUIRE(jstring.getValue() ==  testValue);
}

TEST_CASE( "create JString char value", JSTRING_TEST_TAG ) {
    const char testValue[] = "teststr";
    JString jstring(testValue);
    
    string expectedValue = createExpectedValue(testValue);

    REQUIRE(jstring.toString() ==  expectedValue);
    REQUIRE(jstring.getValue() ==  testValue);
}

#endif