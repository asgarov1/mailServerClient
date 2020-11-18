//
// Created by asgarov1 on 11/17/20.
//

#include <filesystem>
#include "MailService.h"
#include <fstream>
#include <fstream>
#include "../Command.h"
#include "../exception/IllegalCommandException.h"

#define OK "OK\n"
#define ERROR "ERR\n"

using namespace std;

std::string MailService::processMessage(std::__cxx11::basic_string<char> receivedMessage) {
    string command = receivedMessage.substr(0, 4);

    if (!command.compare(SEND)) {
        return processSend(receivedMessage);
    } else if (!command.compare(LIST)) {
        return processList(receivedMessage);
    } else if (!command.compare(READ)) {
        return processRead(receivedMessage);
    } else if (command.find(DEL) != string::npos) {
        return processDel(receivedMessage);
    } else {
        return ERROR;
    }
}

std::string MailService::processSend(std::basic_string<char> receivedMessage) {
    string receiver = readNthLine(3, receivedMessage);
    string fileName = receiver + ".txt";
    string path = filePath + "/" + fileName;

    int endOfFirstLine = receivedMessage.find("\n", 0) + 1;
    if (filesystem::exists(fileName)) {
        ofstream file(fileName, ios::app);
        file << receivedMessage.substr(endOfFirstLine) << endl;
    } else {
        ofstream file{fileName};
        file << receivedMessage.substr(endOfFirstLine) << endl;
    }
}

std::string MailService::processList(std::basic_string<char> receivedMessage) {
    return std::string();
}

std::string MailService::processRead(std::basic_string<char> receivedMessage) {
    return std::string();
}

std::string MailService::processDel(std::basic_string<char> receivedMessage) {
    return std::string();
}

std::string MailService::readNthLine(int n, std::string input) {
    for (int i = 1; i < n; ++i) {
        int endOfLine = input.find("\n", 0) + 1;
        input = input.substr(endOfLine);
    }
    if (input.find("\n", 0) != string::npos) {
        return input.substr(0, input.find("\n", 0));
    }
    return input;
}

MailService::MailService(const string &filePath) {
//    string finalFilePath;
//    if (!filePath.starts_with("/")) {
//        finalFilePath = filesystem::current_path().string() + "/" + filePath;
//    }
//
//    std::filesystem::create_directory(filePath);
    setFilePath(filePath);
}

void MailService::setFilePath(const string &filePath) {
    MailService::filePath = filePath;
}
