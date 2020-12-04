cmake_minimum_required(VERSION 3.17)
project(sockets)

set(CMAKE_CXX_STANDARD 20)

add_executable(mailserver server/main.cpp shared/socket/Socket.cpp shared/socket/Socket.h shared/socket/SocketException.h server/ServerSocket.cpp server/ServerSocket.h server/MailService.cpp server/MailService.h shared/util/StringUtil.cpp shared/util/StringUtil.h server/LoginService.cpp server/LoginService.h)
target_link_libraries(mailserver ldap lber)

add_executable(mailclient client/main.cpp shared/socket/Socket.cpp shared/socket/Socket.h shared/socket/SocketException.h client/ClientSocket.cpp client/ClientSocket.h client/ClientService.cpp client/ClientService.h shared/exception/IllegalMessageFormatException.h shared/util/StringUtil.cpp shared/util/StringUtil.h)
