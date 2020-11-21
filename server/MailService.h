//
// Created by asgarov1 on 11/17/20.
//

#ifndef SOCKETS_MAILSERVICE_H
#define SOCKETS_MAILSERVICE_H


#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class MailService {

public:
    MailService(std::string filePath);

    std::string processMessage(const std::__cxx11::basic_string<char>& basicString);

    std::string processSend(const std::basic_string<char>& string);

    std::string processList(std::basic_string<char> string);

    std::string processRead(std::basic_string<char> string);

    std::string processDel(std::basic_string<char> string);

private:
    std::string filePath;

    std::vector<std::string> findAllTopicsForUser(std::string username);

    std::string getPathForUsername(const std::string &username);
};

#endif //SOCKETS_MAILSERVICE_H
