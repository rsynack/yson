#ifndef INVALID_ROOT_ERROR_H
#define INVALID_ROOT_ERROR_H

#include <string>
#include <stdexcept>

namespace yson {
    class InvalidRootError : public std::runtime_error {
        
        public:
            InvalidRootError(std::string name)
                : std::runtime_error("Invalid root node type '" + name + "'.") {
            }
    };
}

#endif