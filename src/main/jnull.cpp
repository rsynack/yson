#include "include/jnull.h"

using namespace std;
using namespace yson;

JNull::JNull() {
}

const string JNull::toString() const {
    return "null";
}