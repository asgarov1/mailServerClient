//
// Created by asgarov1 on 11/17/20.
//

#ifndef SOCKETS_MAILSERVICE_H
#define SOCKETS_MAILSERVICE_H


static const int TIME_BLOCKED_IN_SECONDS = 1800;

static const int ALLOWED_ATTEMPTS = 3;

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
#include <cmath>
#include "../shared/Command.h"
#include "../shared/exception/IllegalCommandException.h"
#include "../shared/util/StringUtil.h"
#include "LoginService.h"

class MailService {

public:
    explicit MailService(std::string filePath);

    std::string processMessage(const std::basic_string<char> &receivedMessage, const std::string& address);

    std::string processSend(const std::basic_string<char>& string, const std::string& username);

    std::string processList(const std::basic_string<char>& string, const std::string& username);

    std::string processRead(const std::basic_string<char>& string, const std::string& username);

    std::string processDel(const std::basic_string<char>& string, const std::string& username);

private:
    std::mutex myMutex;
    std::string filePath;
    std::map<std::string, std::string> socketAndUsername = {};
    std::map<std::string, int> socketFailedLogins = {};
    std::map<std::string, std::chrono::high_resolution_clock::time_point> socketsBlocked = {};

    std::vector<std::string> findAllTopicsForUser(const std::string& username);

    std::string getPathForUsername(const std::string &username);

    std::string processLogin(const std::basic_string<char> &receivedMessage, const std::string& address);

    void unregisterSocket(const std::string& address);

    bool socketIsRegistered(const std::string &ipAndPort);

    double getSecondsPassed(const std::string &address);
};

#endif //SOCKETS_MAILSERVICE_H
