#include "include/jreader.h"
#include "include/jobject.h"
#include "include/jbool.h"
#include "include/jarray.h"
#include "include/jstring.h"
#include "include/jnumber.h"
#include "include/jnull.h"
#include "include/error/root_not_found_error.h"

#include <sstream>
#include <fstream>

using namespace std;
using namespace yson;

JReader::JReader() {

}

JDocument JReader::parseFile(const char* filename) {
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

    while (istream.good()) {

        if (c == '{') {
            JObject jobject = parseJObject(istream);
            return JDocument(make_shared<JObject>(jobject));
        } else if (c == '[') {
            JArray jarray = parseArray(istream);
            return JDocument(make_shared<JArray>(jarray));
        }

        c = istream.get();
    }

    throw RootNotFoundError();
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
    shared_ptr<JValue> value;

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

    if (value.get() != nullptr) {
        obj._addValue(attrName, value, {});
    }
}

shared_ptr<JValue> JReader::parseValue(istream &ifs) {
    shared_ptr<JValue> value;

    stringstream sstream;

    char c = ifs.get();
    while(ifs.good()) {

        if (c == '{') {
            JObject jobject = parseJObject(ifs);
            value = make_shared<JObject>(jobject);
            break;
        } else if (c == '[') {
            JArray jarray = parseArray(ifs);
            value = make_shared<JArray>(jarray);
            break;
        } else if (c == '"') {
            JString jstring = parseString(ifs);
            value = make_shared<JString>(jstring);
            break;
        } else if (c == ',' || c == '}') {
            break;
        } else if (c == '-') {
            c = ifs.get();
            if (isdigit(c)) {
                JNumber jnumber = parseNumber(ifs, c, true);
                value = make_shared<JNumber>(jnumber);
                break;
            }
        } else if(isdigit(c)) {
            JNumber jnumber = parseNumber(ifs, c, false);
            value = make_shared<JNumber>(jnumber);
            break;
        } if (!isspace(c)) {
            sstream << c;
        }

        c = ifs.get(); 
    }

    string str = sstream.str();
    if (str == "false" || str == "true") {
        JBool boolean(str == "true");
        value = make_shared<JBool>(boolean);
    } else if (str == "null") {
        JNull jnull;
        value = make_shared<JNull>(jnull);
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
