#include "include/jnumber.h"

#include <sstream>
#include <limits>

using namespace std;
using namespace yson;

JNumber::JNumber() {

}

void JNumber::setSinged(int64_t value) {
    this->singedValue = value;
    this->valueType = ValueType::SINGED;
}

void JNumber::setUnsigned(uint64_t value) {
    this->unsingedValue = value;
    this->valueType = ValueType::UNSINGED;
}

void JNumber::setFloating(double value) {
    this->floatingValue = value;
    this->valueType = ValueType::FLOATING;
}

const string JNumber::toString() const {
    stringstream sstream;

    switch(this->valueType) {
        case ValueType::SINGED:
            sstream << this->singedValue;
            break;
        case ValueType::UNSINGED:
            sstream << this->unsingedValue;
            break;
        case ValueType::FLOATING:
            sstream << to_string(this->floatingValue);
            break;
    }

    return sstream.str();
}