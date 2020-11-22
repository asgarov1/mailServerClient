//
// Created by asgarov1 on 11/17/20.
//

#ifndef SOCKETS_CLIENTSOCKET_H
#define SOCKETS_CLIENTSOCKET_H

#include "../shared/socket/Socket.h"

class ClientSocket : private Socket
{
public:

    ClientSocket ( std::string host, int port );
    virtual ~ClientSocket(){};

    const ClientSocket& operator << ( const std::string& ) const;
    const ClientSocket& operator >> ( std::string& ) const;

};


#endif //SOCKETS_CLIENTSOCKET_H
