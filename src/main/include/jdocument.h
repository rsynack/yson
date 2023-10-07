#ifndef JDOCUMENT_H
#define JDOCUMENT_H

#include "jvalue.h"
#include "jobject.h"
#include "jarray.h"
#include "error/invalid_root_error.h"

#include <memory>
#include <string>

namespace yson {

    class JDocument : public JValue {

        private:
            std::shared_ptr<JValue> root;

        public:
            JDocument(std::shared_ptr<JValue> root) {
                this->root = root;
            }

            template<typename T>
            std::shared_ptr<T> getRoot() { 
                return std::dynamic_pointer_cast<T>(this->root);
            }

            std::shared_ptr<JObject> getObject();

            std::shared_ptr<JArray> getArray();

            const std::string toString() const { return this->root->toString(); }

    };

}

#endif