//
// Created by asgarov1 on 11/17/20.
//

#ifndef SOCKETS_SOCKET_H
#define SOCKETS_SOCKET_H


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>


const int MAXCONNECTIONS = 20;
const int MAXRECV = 500;

class Socket {
public:
    Socket();

    virtual ~Socket();

    // Server initialization
    bool create();

    bool bind(int port);

    bool listen() const;

    bool accept(Socket &) const;

    // Client initialization
    bool connect(const std::string &host, const int port);

    bool send(const std::string&) const;

    int recv(std::string &) const;

    bool isValid() const { return m_sock != -1; }

    int m_sock;
    sockaddr_in m_addr{};
};

#endif //SOCKETS_SOCKET_H
