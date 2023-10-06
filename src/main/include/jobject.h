#ifndef JOBJECT_H
#define JOBJECT_H

#include "jvalue.h"
#include "jarray.h"
#include "jnull.h"
#include "jnumber.h"

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <memory>

namespace yson {
 
    class JArray;

    class JObject : public JValue {
        private:
            std::map<std::string, std::shared_ptr<JValue>> values;
            std::vector<std::string> keys;
            std::map<std::string, int> index;

        public:
            JObject();

            template<typename T>
            void _addValue(std::string name, T value) {
                this->keys.push_back(name);
                this->index.emplace(make_pair(name, this->keys.size() - 1));
                this->values.emplace(make_pair(name, value));
            }

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