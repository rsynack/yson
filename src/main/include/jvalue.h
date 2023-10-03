#ifndef JVALUE_H
#define JVALUE_H

#include <string>

namespace yson {

    class JValue {

        public:
            virtual const std::string toString() const = 0;
    };

}

#endif