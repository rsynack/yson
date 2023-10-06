#include "include/jdocument.h"
#include "include/jobject.h"
#include "include/jarray.h"

using namespace std;
using namespace yson;

shared_ptr<JObject> JDocument::getObject() {
    shared_ptr<JObject> value = this->getRoot<JObject>();
    if (value.get()) {
        return value;
    }

    throw InvalidRootError("JObject");
}

shared_ptr<JArray> JDocument::getArray() {
    shared_ptr<JArray> value = this->getRoot<JArray>();
    if (value.get()) {
        return value;
    }

    throw InvalidRootError("JArray");
}