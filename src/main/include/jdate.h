#ifndef JDATE_H
#define JDATE_H

#include <string>

#include "jvalue.h"
#include "jnumber.h"

namespace yson {

    class JDate : public JValue {

        private:
            time_t value;

        public:
            JDate(time_t value);

            const std::string toString() const;
    };
}

#endif