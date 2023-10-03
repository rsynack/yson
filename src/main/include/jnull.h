#ifndef JNULL_H
#define JNULL_H

#include <string>

#include "jvalue.h"

namespace yson {

    class JNull : public JValue {

        public:
            JNull();

            const std::string toString() const;
    };
}


#endif