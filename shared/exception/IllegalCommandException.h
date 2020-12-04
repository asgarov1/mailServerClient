//
// Created by asgarov1 on 11/18/2020.
//

#ifndef SOCKETS_ILLEGALCOMMANDEXCEPTION_H
#define SOCKETS_ILLEGALCOMMANDEXCEPTION_H

#include <exception>
#include <string>

/**
 * Custom exception
 */
class IllegalCommandException : std::exception {
public:
    IllegalCommandException(std::string message) : exceptionMessage(message) {};

    ~IllegalCommandException() {};

    std::string description() { return exceptionMessage; }

protected:
    std::string exceptionMessage;
};

#endif //SOCKETS_ILLEGALCOMMANDEXCEPTION_H
