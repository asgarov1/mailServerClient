//
// Created by asgarov1 on 11/17/20.
//

#include "MailService.h"

#define OK "OK\n"
#define ERROR "ERR\n"

using namespace std;

std::string MailService::processMessage(const std::basic_string<char> &receivedMessage, const std::string &ipAndPort) {
    if (receivedMessage.length() < 4) {
        return string(ERROR) + "Wrong format!" + LINE_BREAK;
    }
    string command = receivedMessage.substr(0, 5);

    if (!socketIsRegistered(ipAndPort)) {
        if (StringUtil::equals(command, LOGIN)) {
            return processLogin(receivedMessage, ipAndPort);
        }
    } else if (socketIsRegistered(ipAndPort)) {
        if (command.find(SEND) != string::npos) {
            return processSend(receivedMessage, ipAndPort);
        } else if (command.find(LIST) != string::npos) {
            return processList(receivedMessage, ipAndPort);
        } else if (command.find(READ) != string::npos) {
            return processRead(receivedMessage, ipAndPort);
        } else if (command.find(DEL) != string::npos) {
            return processDel(receivedMessage, ipAndPort);
        }
    }
    if (command.find(QUIT) != string::npos) {
        unregisterSocket(ipAndPort);
        return OK;
    }
    return ERROR;
}

std::string MailService::processSend(const std::basic_string<char> &receivedMessage, const std::string &ipAndPort) {
    if (StringUtil::numberOfOccurrences(receivedMessage, "\n") < 6) {
        return string(ERROR) + "Wrong format!" + LINE_BREAK;
    }

    string username = StringUtil::readNthLine(2, receivedMessage);
    if (!userIsLoggedIn(ipAndPort, username)) {
        return string(ERROR) + "You can only perform operations for your username!" + LINE_BREAK;
    }

    string receiver = StringUtil::readNthLine(3, receivedMessage);
    string fileName = receiver + ".txt";
    string path = filePath + "/" + fileName;

    mut.lock();
    int endOfFirstLine = receivedMessage.find('\n', 0) + 1;
    if (!filesystem::exists(filePath)) {
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

std::string MailService::processList(const std::basic_string<char> &receivedMessage, const std::string &ipAndPort) {
    if (StringUtil::numberOfOccurrences(receivedMessage, "\n") < 2) {
        return string(ERROR) + "Wrong format!" + LINE_BREAK;
    }

    string username = StringUtil::readNthLine(2, receivedMessage);
    if (!userIsLoggedIn(ipAndPort, username)) {
        return string(ERROR) + "You can only perform operations for your username!" + LINE_BREAK;
    }

    vector<string> topics = findAllTopicsForUser(username);
    string answer = to_string(topics.size()) + LINE_BREAK;
    for (auto &topic : topics) {
        answer += topic + LINE_BREAK;
    }
    return answer;
}

std::string MailService::processRead(const std::basic_string<char> &receivedMessage, const std::string &ipAndPort) {
    if (StringUtil::numberOfOccurrences(receivedMessage, "\n") < 3) {
        return string(ERROR) + "Wrong format!" + LINE_BREAK;
    }

    string username = StringUtil::readNthLine(2, receivedMessage);
    if (!userIsLoggedIn(ipAndPort, username)) {
        return string(ERROR) + "You can only perform operations for your username!" + LINE_BREAK;
    }

    string messageFileText = StringUtil::readFile(getPathForUsername(username));
    if (messageFileText.length() < 1) {
        return ERROR;
    }

    string messageNumberText = StringUtil::readNthLine(3, receivedMessage);
    if (!StringUtil::isNumber(messageNumberText)) {
        return string(ERROR) + "Message number must be a number!" + LINE_BREAK;
    }

    int messageNumber = stoi(messageNumberText) - 1; // -1 because computers count from 0
    vector<string> messages = StringUtil::splitText(messageFileText, "\n\n");

    if (messageNumber < 0 || messageNumber >= messages.size()) {
        return ERROR;
    }

    return OK +
           messages.at(messageNumber);
}

std::string MailService::processDel(const std::basic_string<char> &receivedMessage, const std::string &ipAndPort) {
    if (StringUtil::numberOfOccurrences(receivedMessage, "\n") < 3) {
        return string(ERROR) + "Wrong format!" + LINE_BREAK;
    }

    string username = StringUtil::readNthLine(2, receivedMessage);
    if (!userIsLoggedIn(ipAndPort, username)) {
        return string(ERROR) + "You can only perform operations for your username!" + LINE_BREAK;
    }

    string messageFileText = StringUtil::readFile(getPathForUsername(username));

    int messageNumber = stoi(StringUtil::readNthLine(3, receivedMessage)) - 1;
    vector<string> messages = StringUtil::splitText(messageFileText, "\n\n");

    if (messageNumber < 0 || messageNumber >= messages.size()) {
        return ERROR;
    }
    messages.at(messageNumber) = "";

    mut.lock();
    ofstream myFile;
    myFile.open(getPathForUsername(username));
    myFile << StringUtil::flattenToStringWithDelimeter(messages, "\n\n");
    myFile.close();
    mut.unlock();
    return OK;
}

vector<string> MailService::findAllTopicsForUser(const std::string &username) {
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

MailService::MailService(string filePath) : filePath(std::move(filePath)) {}

std::string MailService::processLogin(const std::basic_string<char> &receivedMessage, const std::string &ipAndPort) {
    if (StringUtil::numberOfOccurrences(receivedMessage, "\n") < 3) {
        return string(ERROR) + "Wrong format!" + LINE_BREAK;
    }

    string username = StringUtil::readNthLine(2, receivedMessage);
    string password = StringUtil::readNthLine(3, receivedMessage);
    if (LoginService::validateCredentials(username, password)) {
        socketAndUsername[ipAndPort] = username;
        return OK;
    } else {
        return string(ERROR) +
               "Invalid credentials!" + LINE_BREAK;
    }
}

void MailService::unregisterSocket(const std::string &ipAndPort) {
    socketAndUsername.erase(ipAndPort);
}

bool MailService::userIsLoggedIn(const std::string &ipAndPort, const std::string &username) {
    return !socketAndUsername.at(ipAndPort).compare(username);
}

bool MailService::socketIsRegistered(const string &ipAndPort) {
    return socketAndUsername.contains(ipAndPort);
}
