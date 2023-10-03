#include "include/jstring.h"

#include <sstream>

using namespace std;
using namespace yson;

JString::JString(string value) {
    this->value = value;
}

const string JString::toString() const {
    stringstream sstream;

    sstream << "\"" << this->value << "\"";

    return sstream.str();
}