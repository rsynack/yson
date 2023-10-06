#ifndef JARRAY_TEST_H
#define JARRAY_TEST_H

#include "catch.hpp"
#include "../main/include/jarray.h"

#include <string>

using namespace std;
using namespace yson;

const string JARRAY_TEST_TAG = "[jarray]";

TEST_CASE( "is include guard macro in jarray.h implemented", JARRAY_TEST_TAG) {
    #ifdef JARRAY_H
        REQUIRE(true);
    #else
        INFO("include guard macro JARRAY_H not implemented");
        REQUIRE(false);
    #endif
}

TEST_CASE( "create empty JArray value", JARRAY_TEST_TAG) {
    JArray array;
    
    REQUIRE(array.toString() ==  "[]");
}

TEST_CASE( "create JArray with number values", JARRAY_TEST_TAG) {

    JArray array;
    array.addNumber((int64_t)1);
    array.addNumber((int64_t)-2);
    array.addNumber((int64_t)3);
    array.addNumber((int64_t)-4);
    
    REQUIRE(array.toString() ==  "[1, -2, 3, -4]");
}

TEST_CASE( "create JArray with unsigned number values", JARRAY_TEST_TAG) {
    JArray array;
    array.addNumber((uint64_t)1);
    array.addNumber((uint64_t)2);
    array.addNumber((uint64_t)3);
    
    REQUIRE(array.toString() ==  "[1, 2, 3]");
}

//TEST_CASE( "create JArray with floating number values", JARRAY_TEST_TAG) {
//    JArray *value = new JArray();
//    value->addNumber(1.12345);
//    value->addNumber(-2.67890);           //should remove ending zeros
//    value->addNumber(3.123456789000);     //should remove ending zeros
//    value->addNumber(-4.0987654321);
//    
//    REQUIRE(value->toString() ==  "[1.12345, -2.6789, 3.123456789, -4.0987654321]");
//}

TEST_CASE( "create JArray with floating number values", JARRAY_TEST_TAG) {
    JArray array;
    array.addNumber(1.123);
    array.addNumber(-2.678);     //should remove ending zeros
    array.addNumber(3.1234);     //should remove ending zeros
    array.addNumber(-4.0987);
    
    REQUIRE(array.toString() ==  "[1.123000, -2.678000, 3.123400, -4.098700]");
}

TEST_CASE( "create JArray with embedded array", JARRAY_TEST_TAG) {
    JArray embeddedArray;
    embeddedArray.addNumber((int64_t)1);
    embeddedArray.addNumber((int64_t)-2);
    embeddedArray.addNumber((int64_t)3);
    embeddedArray.addNumber((int64_t)-4);

    JArray array;
    array.addValue(embeddedArray);
    
    REQUIRE(array.toString() ==  "[[1, -2, 3, -4]]");
}

TEST_CASE( "create JArray with object values", JARRAY_TEST_TAG) {
    JObject obj1;
    obj1.addBoolean("myBool", false);

    JObject obj2;
    obj2.addNumber("myNumber", (int64_t)42);

    JArray array;
    array.addValue(obj1);
    array.addValue(obj2);

    REQUIRE(array.toString() ==  "[{ \"myBool\": false }, { \"myNumber\": 42 }]");
    REQUIRE(!array.getObject(0)->getBoolean("myBool"));
    REQUIRE(array.getObject(1)->getNumber("myNumber")->getSinged() == 42);
}




#endif