//
// Created by asgarov1 on 11/17/20.
//

#ifndef SOCKETS_MAILSERVICE_H
#define SOCKETS_MAILSERVICE_H


#include <string>

class MailService {

public:
    std::string processMessage(std::__cxx11::basic_string<char> basicString);

    std::string processSend();
};


#endif //SOCKETS_MAILSERVICE_H
