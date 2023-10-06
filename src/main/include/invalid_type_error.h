#ifndef INVALID_TYPE_ERROR_H
#define INVALID_TYPE_ERROR_H

#include <string>
#include <stdexcept>

namespace yson {
    class InvalidTypeError : public std::runtime_error {
        
        public:
            InvalidTypeError(std::string name)
                : std::runtime_error("Invalid type for name '" + name + "'.") {
            }

            InvalidTypeError(size_t index)
                : std::runtime_error("Invalid type for index '" + std::to_string(index) + "'.") {
            }
    };
}

#endif