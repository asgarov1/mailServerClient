//
// Created by asgarov1 on 11/18/2020.
//

#ifndef SOCKETS_ILLEGALMESSAGEFORMATEXCEPTION_H
#define SOCKETS_ILLEGALMESSAGEFORMATEXCEPTION_H

#include "ClientSideException.h"

class IllegalMessageFormatException : ClientSideException {
public:
    IllegalMessageFormatException(std::string message) : ClientSideException(message) {};
    ~IllegalMessageFormatException (){};

    std::string description() { return exceptionMessage; }

};

#endif //SOCKETS_ILLEGALMESSAGEFORMATEXCEPTION_H
