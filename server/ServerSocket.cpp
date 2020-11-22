//
// Created by asgarov1 on 11/17/20.
//

#include <iostream>
#include "ServerSocket.h"
#include "../shared/socket/SocketException.h"

ServerSocket::ServerSocket(int port) {
    if (!Socket::create()) {
        throw SocketException("Could not create server socket.");
    }

    if (!Socket::bind(port)) {
        throw SocketException("Could not bind to port.");
    }

    if (!Socket::listen()) {
        throw SocketException("Could not listen to socket.");
    }

}

ServerSocket::~ServerSocket() {
}


const ServerSocket &ServerSocket::operator<<(const std::string &s) const {
    if (!Socket::send(s)) {
        throw SocketException("Could not write to socket.");
    }

    return *this;

}


const ServerSocket &ServerSocket::operator>>(std::string &s) const {
    if (!Socket::recv(s)) {
        throw SocketException("Could not read from socket.");
    }

    return *this;
}

std::string ServerSocket::accept(ServerSocket &sock) {
    if (!Socket::accept(sock)) {
        throw SocketException("Could not accept socket.");
    }
    return inet_ntoa(m_addr.sin_addr) + std::string(":") + std::to_string(ntohs(m_addr.sin_port));
}