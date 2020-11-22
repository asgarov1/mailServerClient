//
// Created by asgarov1 on 11/17/20.
//

#include "MailService.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include "../Command.h"
#include "../exception/IllegalCommandException.h"
#include "../StringUtil.h"

#define OK "OK\n"
#define ERROR "ERR\n"

using namespace std;

std::string MailService::processMessage(const std::__cxx11::basic_string<char> &receivedMessage) {
    string command = receivedMessage.substr(0, 4);
    //TODO message validation

    if (StringUtil::equals(command, SEND)) {
        return processSend(receivedMessage);
    } else if (StringUtil::equals(command, LIST)) {
        return processList(receivedMessage);
    } else if (StringUtil::equals(command, READ)) {
        return processRead(receivedMessage);
    } else if (command.find(DEL) != string::npos) {
        return processDel(receivedMessage);
    } else if (StringUtil::equals(command, QUIT)) {
        return OK;
        //todo logout
    } else {
        return ERROR;
    }
}

std::string MailService::processSend(const std::basic_string<char> &receivedMessage) {
    string receiver = StringUtil::readNthLine(3, receivedMessage);
    string fileName = receiver + ".txt";
    string path = filePath + "/" + fileName;

    mut.lock();
    int endOfFirstLine = receivedMessage.find('\n', 0) + 1;
    if (!filesystem::exists(filePath)){
        mkdir(filePath.c_str(), 0777);
    }

    if (filesystem::exists(path)) {
        ofstream file(path, ios::app);
        file << receivedMessage.substr(endOfFirstLine) << endl;
        file.close();
    } else {
        ofstream file{path};
        file << receivedMessage.substr(endOfFirstLine) << endl;
        file.close();
    }
    mut.unlock();

    return OK;
}

std::string MailService::processList(std::basic_string<char> receivedMessage) {
    string user = StringUtil::readNthLine(2, receivedMessage);
    vector<string> topics = findAllTopicsForUser(user);
    string answer = to_string(topics.size()) + LINE_BREAK;
    for (auto &topic : topics) {
        answer += topic + LINE_BREAK;
    }
    return answer;
}

std::string MailService::processRead(std::basic_string<char> receivedMessage) {
    string username = StringUtil::readNthLine(2, receivedMessage);
    string messageFileText = StringUtil::readFile(getPathForUsername(username));
    if (messageFileText.length() < 1) {
        return ERROR;
    }

    int messageNumber = stoi(StringUtil::readNthLine(3, receivedMessage)) - 1;
    vector<string> messages = StringUtil::splitText(messageFileText, "\n\n");

    if(messageNumber < 0 || messageNumber >= messages.size()){
        return ERROR;
    }

    return OK +
    messages.at(messageNumber); // -1 because computers count from 0
}

std::string MailService::processDel(std::basic_string<char> receivedMessage) {

    string username = StringUtil::readNthLine(2, receivedMessage);
    string messageFileText = StringUtil::readFile(getPathForUsername(username));

    int messageNumber = stoi(StringUtil::readNthLine(3, receivedMessage)) - 1;
    vector<string> messages = StringUtil::splitText(messageFileText, "\n\n");

    if(messageNumber < 0 || messageNumber >= messages.size()){
        return ERROR;
    }
    messages.at(messageNumber) = "";

    mut.lock();
    ofstream myFile;
    myFile.open (getPathForUsername(username));
    myFile << StringUtil::flattenToStringWithDelimeter(messages, "\n\n");
    myFile.close();
    mut.unlock();
    return OK;
}

vector<string> MailService::findAllTopicsForUser(std::string username) {
    std::vector<std::string> topics;
    string messageFileText = StringUtil::readFile(getPathForUsername(username));
    if (messageFileText.length() < 1) {
        return topics;
    }

    vector<string> messages = StringUtil::splitText(messageFileText, "\n\n");
    topics.reserve(messages.size());
    for (auto &message : messages) {
        topics.push_back(StringUtil::readNthLine(3, message));
    }
    return topics;
}

string MailService::getPathForUsername(const string &username) { return filePath + "/" + username + ".txt"; }

MailService::MailService(string filePath) : filePath(std::move(filePath)) {

}

