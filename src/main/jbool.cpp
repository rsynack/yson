#include "include/jbool.h"

using namespace std;
using namespace yson;

JBool::JBool(bool value) {
    this->value = value;
}

const string JBool::toString() const {
    return this->value ? "true" : "false";
}