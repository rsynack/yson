#ifndef JARRAY_H
#define JARRAY_H

#include "jvalue.h"
#include "jobject.h"

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

            void remove(int index);

            const std::string toString() const;
    };
}

#endif