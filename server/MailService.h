//
// Created by asgarov1 on 11/17/20.
//

#ifndef SOCKETS_MAILSERVICE_H
#define SOCKETS_MAILSERVICE_H


static const int TIME_BLOCKED_IN_SECONDS = 1800;

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
#include "../shared/Command.h"
#include "../shared/exception/IllegalCommandException.h"
#include "../shared/util/StringUtil.h"
#include "LoginService.h"

class MailService {

public:
    explicit MailService(std::string filePath);

    std::string processMessage(const std::basic_string<char> &receivedMessage, const std::string& string);

    std::string processSend(const std::basic_string<char>& string, const std::string &ipAndPort);

    std::string processList(const std::basic_string<char>& string, const std::string &ipAndPort);

    std::string processRead(const std::basic_string<char>& string, const std::string &ipAndPort);

    std::string processDel(const std::basic_string<char>& string, const std::string &ipAndPort);

private:
    std::mutex mut;
    std::string filePath;
    std::map<std::string, std::string> socketAndUsername = {};
    std::map<std::string, int> socketFailedLogins = {};
    std::map<std::string, std::chrono::high_resolution_clock::time_point> socketsBlocked = {};

    std::vector<std::string> findAllTopicsForUser(const std::string& username);

    std::string getPathForUsername(const std::string &username);

    std::string processLogin(const std::basic_string<char> &receivedMessage, const std::string& string);

    bool userIsLoggedIn(const std::string &ipAndPort, const std::string &username);

    void unregisterSocket(const std::string& ipAndPort);

    bool socketIsRegistered(const std::string &ipAndPort);

    double getSecondsPassed(const std::string &ipAndPort);
};

#endif //SOCKETS_MAILSERVICE_H
