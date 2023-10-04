#include "include/jobject.h"
#include "include/jvalue.h"
#include "include/jnumber.h"
#include "include/jbool.h"
#include "include/jdate.h"
#include "include/jstring.h"
#include "include/jarray.h"

#include <sstream>

using namespace std;
using namespace yson;

JObject::JObject() {

}

void JObject::addValue(string name, shared_ptr<JValue> value) {
    this->keys.push_back(name);
    this->index.emplace(make_pair(name, this->keys.size() - 1));
    this->values.emplace(make_pair(name, value));
}

void JObject::addValue(string name, JObject value) {
    this->addValue(name, make_shared<JObject>(value));
}

void JObject::addValue(string name, JArray value) {
    this->addValue(name, make_shared<JArray>(value));
}

void JObject::addValue(string name, JNull value) {
    this->addValue(name, make_shared<JNull>(value));
}

void JObject::addNumber(string name, int64_t value) {
    JNumber *number = new JNumber();
    number->add(value);
    this->addValue(name, shared_ptr<JValue>(number));
}

void JObject::addNumber(string name, uint64_t value) {
    JNumber *number = new JNumber();
    number->addUnsigned(value);
    this->addValue(name, shared_ptr<JValue>(number));
}

void JObject::addNumber(string name, double value) {
    JNumber *number = new JNumber();
    number->addFloating(value);
    this->addValue(name, shared_ptr<JValue>(number));
}

void JObject::addBoolean(string name, bool value) {
    JBool *boolean = new JBool(value);
    this->addValue(name, shared_ptr<JValue>(boolean));
}

void JObject::addString(string name, string value) {
    JString *str = new JString(value);
    this->addValue(name, shared_ptr<JValue>(str));
}

void JObject::addDate(string name, time_t time) {
    JDate *date = new JDate(time);
    this->addValue(name, shared_ptr<JValue>(date));
}

shared_ptr<JNumber> JObject::getNumber(string name) {
    return dynamic_pointer_cast<JNumber>(this->values.at(name));
}

void JObject::remove(string name) {
    this->values.erase(name);
    int index = this->index.at(name);
    this->keys.erase(this->keys.begin() + index);
    this->index.erase(name);
}

const string JObject::toString() const {
    stringstream sstream;

    sstream << "{";

    for(size_t i = 0; i < this->keys.size(); i++) {
        const string key = this->keys[i];
        sstream << " \"" << key << "\": ";

        const shared_ptr<JValue> value = this->values.at(key);
        sstream << value->toString();

        if (i < this->keys.size() - 1) {
            sstream << ",";
        }
    }

    sstream << " }";

    return sstream.str();
}