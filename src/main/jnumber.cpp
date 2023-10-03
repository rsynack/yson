#include "include/jnumber.h"

#include <sstream>
#include <limits>

using namespace std;
using namespace yson;

JNumber::JNumber() {

}

void JNumber::add(int64_t value) {
    this->intValue = value;
    this->valueType = ValueType::INT;
}

void JNumber::addUnsigned(uint64_t value) {
    this->uintValue = value;
    this->valueType = ValueType::UINT;
}

void JNumber::addFloating(double value) {
    this->doubleValue = value;
    this->valueType = ValueType::DOUBLE;
}

const string JNumber::convertDoubleValueToString() const {
    ostringstream oss;
    oss.precision(numeric_limits<double>::digits10);
    oss << fixed << this->doubleValue;

    string str = oss.str();

    // Remove padding
    // This must be done in two steps because of numbers like 700.00
    size_t pos1 = str.find_last_not_of("0");
    if(pos1 != string::npos)
        str.erase(pos1+1);

    size_t pos2 = str.find_last_not_of(".");
    if(pos2 != string::npos)
        str.erase(pos2+1);

    return str;
}

const string JNumber::toString() const {
    stringstream sstream;

    switch(this->valueType) {
        case ValueType::INT:
            sstream << this->intValue;
            break;
        case ValueType::UINT:
            sstream << this->uintValue;
            break;
        case ValueType::DOUBLE:
            sstream << to_string(this->doubleValue);
            break;
    }

    return sstream.str();
}