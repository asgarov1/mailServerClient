cmake_minimum_required(VERSION 3.17)
project(sockets)

set(CMAKE_CXX_STANDARD 20)

add_executable(mailserver server/main.cpp Socket.cpp Socket.h SocketException.h server/ServerSocket.cpp server/ServerSocket.h server/MailService.cpp server/MailService.h)
add_executable(mailclient client/main.cpp Socket.cpp Socket.h SocketException.h client/ClientSocket.cpp client/ClientSocket.h client/ClientService.cpp client/ClientService.h exception/IllegalMessageFormatException.h exception/IllegalCommandException.h client/StringUtil.cpp client/StringUtil.h)

# for mytest
add_executable(test mytest/main.cpp server/MailService.cpp server/MailService.h)