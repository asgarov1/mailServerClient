//
// Created by asgarov1 on 11/17/20.
//

#ifndef SOCKETS_MAILSERVICE_H
#define SOCKETS_MAILSERVICE_H


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <mutex>
#include <map>
#include <filesystem>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include "../Command.h"
#include "../exception/IllegalCommandException.h"
#include "../shared/util/StringUtil.h"
#include "LoginService.h"

class MailService {

public:
    MailService(std::string filePath);

    std::string processMessage(const std::basic_string<char> &basicString, std::string string);

    std::string processSend(const std::basic_string<char>& string);

    std::string processList(std::basic_string<char> string);

    std::string processRead(std::basic_string<char> string);

    std::string processDel(const std::basic_string<char>& string);

private:
    std::mutex mut;
    std::string filePath;
    std::vector<std::string> loggedInUsers = {};
    std::map<std::string, int> numberOfTimesUserFailed = {};

    std::vector<std::string> findAllTopicsForUser(const std::string& username);

    std::string getPathForUsername(const std::string &username);

    std::string processLogin(const std::basic_string<char> &receivedMessage);

    void saveUserAsLoggedIn(std::string basicString);

    long userIsLoggedIn(const std::string &username);

    void logoutUser(std::string username);
};

#endif //SOCKETS_MAILSERVICE_H
