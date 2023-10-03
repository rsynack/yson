#include "include/jarray.h"
#include "include/jnumber.h"
#include "include/jbool.h"
#include "include/jstring.h"
#include "include/jdate.h"
#include "include/jobject.h"

#include <sstream>

using namespace yson;
using namespace std;

JArray::JArray() {

}

void JArray::addValue(shared_ptr<JValue> value) {
    this->values.push_back(value);
}

void JArray::addValue(JObject value) {
    this->addValue(make_shared<JObject>(value));
}

void JArray::addValue(JArray value) {
    this->addValue(make_shared<JArray>(value));
}

void JArray::addNumber(int64_t value) {
    JNumber number;
    number.add(value);
    this->addValue(make_shared<JNumber>(number));
}

void JArray::addNumber(uint64_t value) {
    JNumber number;
    number.addUnsigned(value);
    this->addValue(make_shared<JNumber>(number));
}

void JArray::addNumber(double value) {
    JNumber number;
    number.addFloating(value);
    this->addValue(make_shared<JNumber>(number));
}

void JArray::addBoolean(bool value) {
    JBool boolean(value);
    this->addValue(make_shared<JBool>(boolean));
}

void JArray::addString(string value) {
    JString str(value);
    this->addValue(make_shared<JString>(str));
}

void JArray::addDate(time_t time) {
    JDate date(time);
    this->addValue(make_shared<JDate>(date));
}

void JArray::remove(int index) {
    this->values.erase(this->values.begin() + index);
}

const string JArray::toString() const {
    stringstream sstream;

    sstream << "[";

    for(int i = 0; i < this->values.size(); i++) {

        shared_ptr<JValue> jvalue = this->values[i];
        sstream << jvalue->toString();

        if (i < this->values.size() - 1) {
            sstream << ", ";
        }
    }

    sstream << "]";

    return sstream.str();
}