#ifndef EXCEPTION_H
#define EXCEPTION_H

/*
   Simple exception class to be used throughout pdCalc. It can be instantiated with a message, and that message can be returned.
*/

#include <string>

namespace pdCalc {
    class Exception {
        public:
            explicit Exception(const std::string& msg) : msg_(msg){}
            const std::string& what() const {return msg_;}

        private:
            std::string msg_;
    };
}
#endif
