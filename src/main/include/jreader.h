#ifndef JREADER_H
#define JREADER_H

#include "jobject.h"
#include "jbool.h"
#include "jarray.h"
#include "jstring.h"
#include "jnumber.h"
#include "jdocument.h"

#include <fstream>

namespace yson {

    class JReader {
        public:
            JReader();
            JDocument parse(const char* filename);

        private:
            JObject parseJObject(std::ifstream &ifs);
            void parseAttribute(std::ifstream &ifs, JObject &obj);
            JValue* parseValue(std::ifstream &ifs);
            JArray parseArray(std::ifstream &ifs);
            JString parseString(std::ifstream &ifs);
            JNumber parseNumber(std::ifstream &ifs, char c, bool negative);

    };
}

#endif