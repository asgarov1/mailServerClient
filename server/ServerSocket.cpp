//
// Created by asgarov1 on 11/17/20.
//

#include <iostream>
#include "ServerSocket.h"
#include "../shared/socket/SocketException.h"

/**
 * Creates the server, binds to port and listens to connections
 * @param port
 */
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

/**
 * Default constructor
 */
ServerSocket::~ServerSocket() = default;


/**
 * Overloaded parameter for comfort of sending messages
 * @param input
 * @return
 */
const ServerSocket &ServerSocket::operator<<(const std::string &input) const {
    if (!Socket::send(input)) {
        throw SocketException("Could not write to socket.");
    }
    return *this;
}

/**
 * Overloaded parameter for comfort of receiving messages
 * @param input
 * @return
 */
const ServerSocket &ServerSocket::operator>>(std::string &input) const {
    if (!Socket::recv(input)) {
        throw SocketException("Could not read from socket.");
    }
    return *this;
}

/**
 * Accepts connections and returns ip:port that is later used to track which user is logged in from which address
 * @param sock
 * @return
 */
std::string ServerSocket::accept(ServerSocket &sock) {
    if (!Socket::accept(sock)) {
        throw SocketException("Could not accept socket.");
    }
    return inet_ntoa(m_addr.sin_addr) + std::string(":") + std::to_string(ntohs(m_addr.sin_port));
}