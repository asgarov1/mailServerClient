//
// Created by asgarov1 on 11/17/20.
//

#include "Socket.h"
#include <cstring>
#include <cerrno>
#include <iostream>


/**
 * Socket constructor, memsets the socket
 */
Socket::Socket() : m_sock(-1) {
    memset(&m_addr, 0, sizeof(m_addr));
}

/**
 * Destructor, closes socket
 */
Socket::~Socket() {
    if (isValid()) {
        ::close(m_sock);
    }
}

/**
 * creates socket
 * @return
 */
bool Socket::create() {
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (!isValid()) {
        return false;
    }

    int on = 1;
    if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char *) &on, sizeof(on)) == -1) {
        return false;
    }
    return true;
}


/**
 * binds to port
 * @param port
 * @return
 */
bool Socket::bind(const int port) {
    if (!isValid()) {
        return false;
    }

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons(port);

    int bind_return = ::bind(m_sock, (struct sockaddr *) &m_addr, sizeof(m_addr));
    if (bind_return == -1) {
        return false;
    }
    return true;
}

/**
 * Listens for cconnections
 * @return
 */
bool Socket::listen() const {
    if (!isValid()) {
        return false;
    }
    int listen_return = ::listen(m_sock, MAXCONNECTIONS);
    if (listen_return == -1) {
        return false;
    }
    return true;
}

/**
 * accepts connection
 * @param new_socket
 * @return
 */
bool Socket::accept(Socket &new_socket) const {
    int addr_length = sizeof(m_addr);
    new_socket.m_sock = ::accept(m_sock, (sockaddr *) &m_addr, (socklen_t *) &addr_length);
    if (new_socket.m_sock <= 0) {
        return false;
    }
    return true;
}

/**
 * sends input
 * @param input
 * @return
 */
bool Socket::send(const std::string& input) const {
    int status = ::send(m_sock, input.c_str(), input.size(), MSG_NOSIGNAL);
    if (status == -1) {
        return false;
    }
    return true;
}

/**
 * received input
 * @param input
 * @return
 */
int Socket::recv(std::string &input) const {
    char buf[MAXRECV + 1];
    input = "";
    memset(buf, 0, MAXRECV + 1);
    int status = ::recv(m_sock, buf, MAXRECV, 0);
    if (status == -1) {
        std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
        return 0;
    } else if (status == 0) {
        return 0;
    }
    input = buf;
    return status;
}

/**
 * connects to server (used by client)
 * @param host
 * @param port
 * @return
 */
bool Socket::connect(const std::string &host, const int port) {
    if (!isValid()) {
        return false;
    }
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);
    if (errno == EAFNOSUPPORT) {
        return false;
    }
    int status = ::connect(m_sock, (sockaddr *) &m_addr, sizeof(m_addr));
    if (status == 0) {
        return true;
    }
    return false;
}
