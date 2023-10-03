#include "include/jdate.h"
#include "include/jnumber.h"

using namespace std;
using namespace yson;

JDate::JDate(time_t value) {
    this->value = value;
}

const string JDate::toString() const {

    char time[size("yyyy-mm-ddThh:MM::ssZ")];
    strftime(time, size(time), "%FT%TZ", gmtime(&this->value));

    return time;
}