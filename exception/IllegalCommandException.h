//
// Created by asgarov1 on 11/18/2020.
//

#ifndef SOCKETS_ILLEGALCOMMANDEXCEPTION_H
#define SOCKETS_ILLEGALCOMMANDEXCEPTION_H

#include <exception>
#include <string>
#include "ClientSideException.h"

class IllegalCommandException : ClientSideException {
public:
    IllegalCommandException (std::string message) : ClientSideException(message) {};
    ~IllegalCommandException (){};

    std::string description() { return exceptionMessage; }

};

#endif //SOCKETS_ILLEGALCOMMANDEXCEPTION_H
