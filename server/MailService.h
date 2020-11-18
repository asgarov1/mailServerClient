//
// Created by asgarov1 on 11/17/20.
//

#ifndef SOCKETS_MAILSERVICE_H
#define SOCKETS_MAILSERVICE_H


#include <string>
#include <iostream>
#include <fstream>

class MailService {

public:
    MailService(const std::string &filePath);

public:
    std::string processMessage(std::__cxx11::basic_string<char> basicString);

    std::string processSend(std::basic_string<char> string);

    std::string processList(std::basic_string<char> string);

    std::string processRead(std::basic_string<char> string);

    std::string processDel(std::basic_string<char> string);

    std::string readNthLine(int n, std::string input);

private:
    std::string filePath;

public:
    void setFilePath(const std::string &filePath);
};

#endif //SOCKETS_MAILSERVICE_H
