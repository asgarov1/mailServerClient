//
// Created by asgarov1 on 11/18/2020.
//

#ifndef SOCKETS_CLIENTSIDEEXCEPTION_H
#define SOCKETS_CLIENTSIDEEXCEPTION_H

#include <exception>
#include <string>

class ClientSideException : std::exception{
public:
    ClientSideException ( std::string message ) : exceptionMessage (message) {};
    ~ClientSideException (){};

    std::string description() { return exceptionMessage; }

protected:
    std::string exceptionMessage;
};

#endif //SOCKETS_CLIENTSIDEEXCEPTION_H
