//
// Created by asgarov1 on 11/17/20.
//

#ifndef SOCKETS_SERVERSOCKET_H
#define SOCKETS_SERVERSOCKET_H


#include <string>
#include "../Socket.h"

class ServerSocket : private Socket
{
public:

    ServerSocket ( int port );
    ServerSocket (){};
    virtual ~ServerSocket();

    const ServerSocket& operator << ( const std::string& ) const;
    const ServerSocket& operator >> ( std::string& ) const;

    void accept ( ServerSocket& );

};

#endif //SOCKETS_SERVERSOCKET_H
