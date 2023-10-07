#ifndef JOBJECT_H
#define JOBJECT_H

#include "jvalue.h"
#include "jarray.h"
#include "jnull.h"
#include "jnumber.h"
#include "invalid_type_error.h"

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <memory>

namespace yson {
 
    class JReader;
    class JArray;

    class JObject : public JValue {

        class AddValueKey {
            friend JReader;

            private:
                AddValueKey() {}
                AddValueKey(AddValueKey const&) = default;
        };

        private:
            std::map<std::string, std::shared_ptr<JValue>> values;
            std::vector<std::string> keys;
            std::map<std::string, int> index;
            
            template<typename T>
            std::shared_ptr<T> getValue(std::string name) {
                if (!this->values.empty() && this->values.find(name) != this->values.end()) {
                    std::shared_ptr<T> value = std::dynamic_pointer_cast<T>(this->values.at(name));
                    if (value) {
                        return value;
                    }
                }

                throw InvalidTypeError(name);
            }

            template<typename T>
            void _addValue(std::string name, T value) {
                this->keys.push_back(name);
                this->index.emplace(make_pair(name, this->keys.size() - 1));
                this->values.emplace(make_pair(name, value));
            }

        public:
            JObject();

            template<typename T>
            void _addValue(std::string name, T value, AddValueKey) { this->_addValue(name, value); };

            void addValue(std::string name, JObject value);
            void addValue(std::string name, JArray value);
            void addValue(std::string name, JNull value);

            void addNumber(std::string name, int64_t value);
            void addNumber(std::string name, uint64_t value);
            void addNumber(std::string name, double value);

            void addBoolean(std::string name, bool value);
            void addString(std::string name, std::string value);
            void addDate(std::string name, time_t time);

            std::shared_ptr<JNumber> getNumber(std::string name);
            bool getBoolean(std::string name);
            std::string getString(std::string name);
            time_t getDate(std::string name);

            void remove(std::string name);

            const std::string toString() const;
    };

}

#endif