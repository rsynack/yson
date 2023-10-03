#ifndef JSTRING_H
#define JSTRING_H

#include "jvalue.h"

#include <string>

namespace yson {

    class JString : public JValue {

        private:
            std::string value;

        public:
            JString(std::string value);

            const std::string toString() const;

    };

}

#endif