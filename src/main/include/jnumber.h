#ifndef JNUMBER_H
#define JNUMBER_H

#include <iostream>

#include "jvalue.h"

namespace yson {

    class JNumber : public JValue {

        enum ValueType { SINGED, UNSINGED, FLOATING };

        private:
            int64_t singedValue;
            uint64_t unsingedValue;
            double floatingValue;

            ValueType valueType;

            const std::string convertDoubleValueToString() const;

        public:
            JNumber();

            void setSinged(int64_t number);
            void setUnsigned(uint64_t number);
            void setFloating(double number);

            int64_t getSinged() {
                return this->singedValue;
            }

            uint64_t getUnsinged() {
                return this->unsingedValue;
            }

            double getFloating() {
                return this->floatingValue;
            }

            const std::string toString() const;
    };
}


#endif