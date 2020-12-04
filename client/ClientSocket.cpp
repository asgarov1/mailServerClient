//
// Created by asgarov1 on 11/17/20.
//

#include "ClientSocket.h"
#include "../shared/socket/SocketException.h"


/**
 * Constructor that creates the sockets and connects to host
 * @param host
 * @param port
 */
ClientSocket::ClientSocket(const std::string& host, int port) {
    if (!Socket::create()) {
        throw SocketException("Couldn't create client socket.");
    }
    if (!Socket::connect(host, port)) {
        throw SocketException("Couldn't bind to port.");
    }
}

/**
 * overloaded an operator for comfortable sending of messages
 * @param input
 * @return
 */
const ClientSocket &ClientSocket::operator<<(const std::string &input) const {
    if (!Socket::send(input)) {
        throw SocketException("Couldn't write to socket.");
    }
    return *this;
}

/**
 * overloaded an operator for comfortable receiving of messages
 * @param input
 * @return
 */
const ClientSocket &ClientSocket::operator>>(std::string &input) const {
    if (!Socket::recv(input)) {
        throw SocketException("Couldn't read from socket.");
    }
    return *this;
}