#ifndef JARRAY_H
#define JARRAY_H

#include "jvalue.h"
#include "jobject.h"
#include "jnumber.h"
#include "jbool.h"
#include "error/invalid_type_error.h"

#include <vector>
#include <memory>
#include <iostream>

namespace yson {

    class JObject;

    class JArray : public JValue {

        private:
            std::vector<std::shared_ptr<JValue>> values;

        public:
            JArray();

            void addValue(std::shared_ptr<JValue> value);
            void addValue(JArray value);
            void addValue(JObject value);
            void addNumber(int64_t value);
            void addNumber(uint64_t value);
            void addNumber(double value);
            void addBoolean(bool value);
            void addString(std::string value);
            void addDate(time_t time);

            template<typename T>
            std::shared_ptr<T> get(size_t index) {
                std::shared_ptr<T> value = std::dynamic_pointer_cast<T>(this->values.at(index));
                if (value.get()) {
                    return value;
                }

                throw InvalidTypeError(index);
            }

            std::shared_ptr<JObject> getObject(size_t index) {
                return get<JObject>(index);
            }

            std::shared_ptr<JNumber> getNumber(size_t index) {
                return get<JNumber>(index);
            }

            bool getBoolean(size_t index) {
                return get<JBool>(index)->getValue();
            }

            void remove(int index);

            const std::string toString() const;
    };
}

#endif