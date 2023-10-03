#ifndef JNUMBER_H
#define JNUMBER_H

#include <iostream>

#include "jvalue.h"

namespace yson {

    class JNumber : public JValue {

        enum ValueType { INT, UINT, DOUBLE };

        private:
            int64_t intValue;
            uint64_t uintValue;
            double doubleValue;

            ValueType valueType;

            const std::string convertDoubleValueToString() const;

        public:
            JNumber();

            void add(int64_t number);
            void addUnsigned(uint64_t number);
            void addFloating(double number);

            const std::string toString() const;
    };
}


#endif