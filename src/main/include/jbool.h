#ifndef JBOOL_H
#define JBOOL_H

#include <string>

#include "jvalue.h"

namespace yson {

    class JBool : public JValue {

        private:
            bool value;

        public:
            JBool(bool value);

            const std::string toString() const;
    };
}


#endif