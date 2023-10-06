#ifndef JNULL_H
#define JNULL_H

#include "jvalue.h"

#include <string>

namespace yson {

    class JNull : public JValue {

        public:
            JNull();

            const std::string toString() const;
    };
}


#endif