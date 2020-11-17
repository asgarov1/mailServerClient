cmake_minimum_required(VERSION 3.17)
project(sockets)

set(CMAKE_CXX_STANDARD 20)

add_executable(server server/main.cpp Socket.cpp Socket.h SocketException.h server/ServerSocket.cpp server/ServerSocket.h server/MailService.cpp server/MailService.h)
add_executable(client client/main.cpp Socket.cpp Socket.h SocketException.h client/ClientSocket.cpp client/ClientSocket.h client/ClientService.cpp client/ClientService.h)