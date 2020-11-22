//
// Created by asgarov1 on 11/17/20.
//

#ifndef SOCKETS_SOCKETEXCEPTION_H
#define SOCKETS_SOCKETEXCEPTION_H

#include <string>

class SocketException : std::exception{
public:
    SocketException ( std::string s ) : exceptionMessage (s ) {};
    ~SocketException (){};

    std::string description() { return exceptionMessage; }

private:
    std::string exceptionMessage;
};

#endif //SOCKETS_SOCKETEXCEPTION_H
