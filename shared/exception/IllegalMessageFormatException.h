//
// Created by asgarov1 on 11/18/2020.
//

#ifndef SOCKETS_ILLEGALMESSAGEFORMATEXCEPTION_H
#define SOCKETS_ILLEGALMESSAGEFORMATEXCEPTION_H

#include <exception>
#include <string>

/**
 * Custom exception
 */
class IllegalMessageFormatException : std::exception {
public:
    IllegalMessageFormatException(std::string message) : exceptionMessage(message) {};

    ~IllegalMessageFormatException() {};

    std::string description() { return exceptionMessage; }

protected:
    std::string exceptionMessage;
};

#endif //SOCKETS_ILLEGALMESSAGEFORMATEXCEPTION_H
