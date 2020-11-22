//
// Created by asgarov1 on 11/17/20.
//

#include <iostream>
#include "ClientService.h"
#include "../Command.h"
#include "../exception/IllegalMessageFormatException.h"
#include "../exception/IllegalCommandException.h"
#include "../StringUtil.h"


using namespace std;

std::string ClientService::prepareMessage(std::__cxx11::basic_string<char> command) {
    if (!command.compare(SEND)) {
        return processSend();
    } else if (!command.compare(LIST)) {
        return processList();
    } else if (!command.compare(READ)) {
        return processRead();
    } else if (!command.compare(DEL)) {
        return processDel();
    } else if (!command.compare(QUIT)) {
        return QUIT;
    } else {
        throw IllegalCommandException("Wrong command was entered");
    }
}

std::string ClientService::processSend() {
    string sender = inputLine("Sender", USERNAME_MAX_LENGTH);
    string recipient = inputLine("Recipient", USERNAME_MAX_LENGTH);
    string topic = inputLine("Topic", TOPIC_MAX_LENGTH);
    string message = inputLine("Message", NO_LIMIT);

    string result =
            string(SEND) + LINE_BREAK +
            sender + LINE_BREAK +
            recipient + LINE_BREAK +
            topic + LINE_BREAK +
            message + LINE_BREAK +
            MESSAGE_END;
    return result;
}

std::string ClientService::processList() {
    string username = inputLine("Username", USERNAME_MAX_LENGTH);

    return string(LIST) + LINE_BREAK +
           username + LINE_BREAK;
}

std::string ClientService::processRead() {
    string username = inputLine("Username", USERNAME_MAX_LENGTH);
    string messageNumber = inputLine("Message Number", NO_LIMIT);
    if (!isInteger(messageNumber)) {
        throw IllegalMessageFormatException(messageNumber + " is not a number");
    }
    return string(READ) + LINE_BREAK +
           username + LINE_BREAK +
           messageNumber + LINE_BREAK;
}

std::string ClientService::processDel() {
    string username = inputLine("Username", USERNAME_MAX_LENGTH);
    string messageNumber = inputLine("Message Number", NO_LIMIT);
    if (!isInteger(messageNumber)) {
        throw IllegalMessageFormatException(messageNumber + " is not a number");
    }
    return string(DEL) + LINE_BREAK +
           username + LINE_BREAK +
           messageNumber + LINE_BREAK;
}

basic_string<char> ClientService::inputLine(const string &inputName, int maxLengthAllowed) const {
    string input;
    string maxLengthMessage =
            maxLengthAllowed == NO_LIMIT ? " " : ", max " + to_string(maxLengthAllowed) + " characters: ";
    cout << "Please enter the " + StringUtil::toLower(inputName) + maxLengthMessage;
    getline(cin, input);

    if (maxLengthAllowed != NO_LIMIT && input.length() > maxLengthAllowed) {
        throw IllegalMessageFormatException(inputName + " name must be max 8 characters!");
    }

    return input;
}

bool ClientService::isInteger(const std::string &input) {
    if (input.empty() || ((!isdigit(input[0])) && (input[0] != '-') && (input[0] != '+'))) return false;

    char *p;
    strtol(input.c_str(), &p, 10);

    return (*p == 0);
}