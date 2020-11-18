//
// Created by asgarov1 on 11/17/20.
//

#include <iostream>
#include "ClientService.h"
#include "../Command.h"
#include "../exception/IllegalMessageFormatException.h"
#include "../exception/IllegalCommandException.h"
#include "StringUtil.h"


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
    } else {
        throw IllegalCommandException("Wrong command was entered");
    }
}

std::string ClientService::processSend() {
    string sender = inputLine("Sender", SENDER_MAX_LENGTH);
    string recipient = inputLine("Recipient", RECIPIENT_MAX_LENGTH);
    string topic = inputLine("Topic", TOPIC_MAX_LENGTH);
    string message = inputLine("Message", NO_LIMIT);

    string result =
            string(SEND) + LINE_BREAK +
            sender +
            recipient +
            topic +
            message +
            MESSAGE_END;
    return result;
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

    return input + LINE_BREAK;
}

std::string ClientService::processList() {
    return std::string();
}

std::string ClientService::processRead() {
    return std::string();
}

std::string ClientService::processDel() {
    return std::string();
}
