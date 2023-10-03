#include "include/jreader.h"
#include "include/jobject.h"
#include "include/jbool.h"
#include "include/jarray.h"
#include "include/jstring.h"
#include "include/jnumber.h"
#include "include/jnull.h"

#include <sstream>
#include <fstream>

using namespace std;
using namespace yson;

JReader::JReader() {

}

JDocument JReader::parse(const char* filename) {
    std::ifstream ifs;

    ifs.open(filename, std::ifstream::in);

    char c = ifs.get();

    JValue *value = nullptr;

    bool isObject = false;
    while (ifs.good()) {

        if (c == '{') {
            JObject jobject = parseJObject(ifs);
            value = &jobject;
            isObject = true;
        } else if (c == '[') {
            JArray jarray = parseArray(ifs);
            value = &jarray;
        }

        c = ifs.get();
    }

    ifs.close();
    
    if (isObject) {
        shared_ptr<JObject> ptr(dynamic_cast<JObject*>(value));
        return JDocument(ptr);
    }

    shared_ptr<JArray> ptr(dynamic_cast<JArray*>(value));
    return JDocument(ptr);
}

JObject JReader::parseJObject(std::ifstream &ifs) {
    JObject obj;

    char c = ifs.get();
    while(ifs.good()) {
        if(c == '"') {
            parseAttribute(ifs, obj);
        } if (c == '}') {
            break;
        }

        c = ifs.get();
    }

    return obj;
}

void JReader::parseAttribute(std::ifstream &ifs, JObject &obj) {
    
    stringstream sstream;
    string attrName;
    JValue *value = nullptr;

    char c = ifs.get();
    while(ifs.good()) {

        if(c == '"') {
            attrName = sstream.str();
            sstream.clear();
        } else if( c == ':') {
            value = parseValue(ifs);
            break;
        }

        sstream << c;

        c = ifs.get();
    }

    if (value != nullptr) {
        shared_ptr<JValue> ptr(value);
        obj.addValue(attrName, ptr);
    }
}

JValue* JReader::parseValue(std::ifstream &ifs) {
    JValue *value = nullptr;

    stringstream sstream;

    char c = ifs.get();
    while(ifs.good()) {

        if (c == '{') {
            JObject jobject = parseJObject(ifs);
            value = &jobject;
            break;
        } else if (c == '[') {
            JArray jarray = parseArray(ifs);
            value = &jarray;
            break;
        } else if (c == '"') {
            JString jstring = parseString(ifs);
            value = &jstring;
            break;
        } else if (c == ',' || c == '}') {
            break;
        } else if (c == '-') {
            c = ifs.get();
            if (isdigit(c)) {
                JNumber jnumber = parseNumber(ifs, c, true);
                value = &jnumber;
                break;
            }
        } else if(isdigit(c)) {
            JNumber jnumber = parseNumber(ifs, c, false);
            value = &jnumber;
            break;
        } if (!isspace(c)) {
            sstream << c;
        }

        c = ifs.get(); 
    }

    string str = sstream.str();
    if (str == "false" || str == "true") {
        value = new JBool(str == "true");
    } else if (str == "null") {
        value = new JNull();
    } 
    
    return value;
}

JArray JReader::parseArray(std::ifstream &ifs) {

    JArray array;

    shared_ptr<JValue> ptr(parseValue(ifs));
    array.addValue(ptr);
    
    char c = ifs.get();
    while(ifs.good()) {
        
        if(c == ']') {
            break;
        }

        shared_ptr<JValue> ptr(parseValue(ifs));
        array.addValue(ptr);

        c = ifs.get();
    } 

    return array;
}


JString JReader::parseString(std::ifstream &ifs) {

    stringstream sstream;
    
    while(ifs.good()) {

        char c = ifs.get();

        if (c == '"') {
            break;
        }

        sstream << c;
    }

    return JString(sstream.str());
}

JNumber JReader::parseNumber(std::ifstream &ifs, char c, bool negative) {
    bool floatingPoint = false;
    stringstream sstream;

    if (negative) {
        sstream << "-";
    }

    sstream << c;
    
    while(ifs.good()) {

        char c = ifs.get();
        if (c == ',') {
            break;
        } else if (!isspace(c)) {
            sstream << c;
        }

        if(c == '.') {
            floatingPoint = true;
        }

    }

    JNumber jnumber;
    string numberStr = sstream.str();
    if (floatingPoint) {
        double number = stod(numberStr);
        jnumber.addFloating(number);
    } else if(negative) {
        int64_t number;
        sstream >> number;
        jnumber.add(number);
    } else {
        uint64_t number;
        sstream >> number;
        jnumber.addUnsigned(number);
    }

    return jnumber;
}
