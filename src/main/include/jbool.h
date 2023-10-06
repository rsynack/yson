#ifndef JBOOL_H
#define JBOOL_H

#include "jvalue.h"

#include <string>

namespace yson {

    class JBool : public JValue {

        private:
            bool value;

        public:
            JBool(bool value);

            bool getValue() { return this->value; }

            const std::string toString() const;
    };
}


#endif