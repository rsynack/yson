#ifndef JNUMBER_H
#define JNUMBER_H

#include "jvalue.h"

#include <iostream>

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

            const int64_t getSinged() const {
                return this->singedValue;
            }

            const uint64_t getUnsinged() const {
                return this->unsingedValue;
            }

            const double getFloating() const {
                return this->floatingValue;
            }
            
            const std::string toString() const;
    };
}


#endif