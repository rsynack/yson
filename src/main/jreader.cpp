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
    ifstream ifs;

    ifs.open(filename, ifstream::in);

    JDocument jdocument = parse(ifs);

    ifs.close();

    return jdocument;
}

JDocument JReader::parse(string json) {
    istringstream strstream(json);
    return parse(strstream);
}

JDocument JReader::parse(istream &istream) {
    char c = istream.get();

    JValue *value = nullptr;

    bool isObject = false;
    while (istream.good()) {

        if (c == '{') {
            JObject jobject = parseJObject(istream);
            value = &jobject;
            isObject = true;
        } else if (c == '[') {
            JArray jarray = parseArray(istream);
            value = &jarray;
        }

        c = istream.get();
    }
    
    if (isObject) {
        shared_ptr<JObject> ptr(dynamic_cast<JObject*>(value));
        return JDocument(ptr);
    }

    shared_ptr<JArray> ptr(dynamic_cast<JArray*>(value));
    return JDocument(ptr);
}

JObject JReader::parseJObject(istream &ifs) {
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

void JReader::parseAttribute(istream &ifs, JObject &obj) {
    
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
        obj._addValue(attrName, ptr);
    }
}

JValue* JReader::parseValue(istream &ifs) {
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

JArray JReader::parseArray(istream &ifs) {

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


JString JReader::parseString(istream &ifs) {

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

JNumber JReader::parseNumber(istream &ifs, char c, bool negative) {
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
        jnumber.setFloating(number);
    } else if(negative) {
        int64_t number;
        sstream >> number;
        jnumber.setSinged(number);
    } else {
        uint64_t number;
        sstream >> number;
        jnumber.setUnsigned(number);
    }

    return jnumber;
}
