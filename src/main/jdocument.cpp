#include "include/jdocument.h"

using namespace std;
using namespace yson;

JDocument::JDocument(shared_ptr<JValue> root) {
    this->root = root;
}

shared_ptr<JValue> JDocument::getRoot() {
    return this->root;
}

const string JDocument::toString() const {
    return this->root->toString();
}