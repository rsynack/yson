#ifndef JDOCUMENT_H
#define JDOCUMENT_H

#include <memory>
#include <string>

#include "jvalue.h"

namespace yson {

    class JDocument : public JValue {

        private:
            std::shared_ptr<JValue> root;

        public:
            JDocument(std::shared_ptr<JValue> root);
            std::shared_ptr<JValue> getRoot();
            const std::string toString() const;
    };

}

#endif