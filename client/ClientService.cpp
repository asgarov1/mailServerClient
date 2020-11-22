//
// Created by asgarov1 on 11/17/20.
//

#include <iostream>
#include <unistd.h>
#include <termios.h>
#include "ClientService.h"
#include "../Command.h"
#include "../exception/IllegalMessageFormatException.h"
#include "../exception/IllegalCommandException.h"
#include "../StringUtil.h"

static const char *const SEPERATION_CHARACTER = " | ";

using namespace std;

std::string ClientService::prepareMessage(std::__cxx11::basic_string<char> command) {
    if (loggedIn) {
        if (StringUtil::equals(command, SEND)) {
            return processSend();
        } else if (StringUtil::equals(command, LIST)) {
            return processList();
        } else if (StringUtil::equals(command, READ)) {
            return processRead();
        } else if (StringUtil::equals(command, DEL)) {
            return processDel();
        }
    } else {
        if (StringUtil::equals(command, LOGIN)) {
            return processLogin();
        }
    }

    if (StringUtil::equals(command, QUIT)) {
        return QUIT;
    }
    throw IllegalCommandException("Wrong command was entered");
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

std::string ClientService::processLogin() {
    string username = inputLine("Username", USERNAME_MAX_LENGTH);

    setStdinEcho(false);
    string password = inputLine("Password", NO_LIMIT);
    cout << endl;
    setStdinEcho(true);

    return string(LOGIN) + LINE_BREAK +
           username + LINE_BREAK +
           password + LINE_BREAK;
}

void ClientService::displayOptions() {
    cout << "Available commands are: ";
    if(!loggedIn){
        cout << string(LOGIN) + SEPERATION_CHARACTER;
    } else {
        cout << string(SEND) + SEPERATION_CHARACTER +
                LIST + SEPERATION_CHARACTER +
                READ + SEPERATION_CHARACTER +
                DEL + SEPERATION_CHARACTER;
    }
    cout << QUIT << endl;
}

void ClientService::setStdinEcho(bool enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

