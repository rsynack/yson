#ifndef JDATE_H
#define JDATE_H

#include "jvalue.h"
#include "jnumber.h"

#include <string>

namespace yson {

    class JDate : public JValue {

        private:
            time_t value;

        public:
            JDate(time_t value);

            time_t getValue() { return this->value; }

            const std::string toString() const;
    };
}

#endif