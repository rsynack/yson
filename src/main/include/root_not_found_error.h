#ifndef ROOT_NOT_FOUND_ERROR_H
#define ROOT_NOT_FOUND_ERROR_H

#include <string>
#include <stdexcept>

namespace yson {
    class RootNotFoundError : public std::runtime_error {
        
        public:
            RootNotFoundError()
                : std::runtime_error("Root not found in JSON.") {
            }
    };
}

#endif