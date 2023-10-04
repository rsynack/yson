#ifndef JREADER_H
#define JREADER_H

#include "jobject.h"
#include "jbool.h"
#include "jarray.h"
#include "jstring.h"
#include "jnumber.h"
#include "jdocument.h"

#include <istream>

namespace yson {

    class JReader {
        public:
            JReader();
            JDocument parse(const char* filename);
            JDocument parse(std::istream &ifs);
            JDocument parse(std::string json);

        private:
            JObject parseJObject(std::istream &ifs);
            void parseAttribute(std::istream &ifs, JObject &obj);
            JValue* parseValue(std::istream &ifs);
            JArray parseArray(std::istream &ifs);
            JString parseString(std::istream &ifs);
            JNumber parseNumber(std::istream &ifs, char c, bool negative);

    };
}

#endif