//
// Created by asgarov1 on 11/17/20.
//

#include <iostream>
#include <unistd.h>
#include <termios.h>
#include "ClientService.h"
#include "../shared/Command.h"
#include "../shared/exception/IllegalMessageFormatException.h"
#include "../shared/exception/IllegalCommandException.h"
#include "../shared/util/StringUtil.h"

static const char *const SEPERATION_CHARACTER = " | ";

using namespace std;

/**
 * On a basis of a passed command prompts user for corresponding input to prepare a complete message to send
 * If user is logged in it will process one of commands, otherwise LOGIN and QUIT are the only options
 * @param command
 * @return
 */
std::string ClientService::prepareMessage(const std::__cxx11::basic_string<char>& command) {
    if (loggedIn) {
        if (command == SEND) {
            return processSend();
        } else if (command == LIST) {
            return processList();
        } else if (command == READ) {
            return processRead();
        } else if (command == DEL) {
            return processDel();
        }
    } else {
        if (command == LOGIN) {
            return processLogin();
        }
    }

    if (command == QUIT) {
        return QUIT;
    }
    throw IllegalCommandException("Wrong command was entered");
}

/**
 * Prompts for inputs and construct the message for SEND command
 * @return
 */
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

/**
 * Prompts for inputs and construct the message for LIST command
 * @return
 */
std::string ClientService::processList() {
    string username = inputLine("Username", USERNAME_MAX_LENGTH);

    return string(LIST) + LINE_BREAK +
           username + LINE_BREAK;
}

/**
 * Prompts for inputs and construct the message for READ command
 * @return
 */
std::string ClientService::processRead() {
    string username = inputLine("Username", USERNAME_MAX_LENGTH);
    string messageNumber = inputLine("Message Number", NO_LIMIT);
    if (!StringUtil::isNumber(messageNumber)) {
        throw IllegalMessageFormatException(messageNumber + " is not a number");
    }
    return string(READ) + LINE_BREAK +
           username + LINE_BREAK +
           messageNumber + LINE_BREAK;
}

/**
 * Prompts for inputs and construct the message for DEL command
 * @return
 */
std::string ClientService::processDel() {
    string username = inputLine("Username", USERNAME_MAX_LENGTH);
    string messageNumber = inputLine("Message Number", NO_LIMIT);
    if (!StringUtil::isNumber(messageNumber)) {
        throw IllegalMessageFormatException(messageNumber + " is not a number");
    }
    return string(DEL) + LINE_BREAK +
           username + LINE_BREAK +
           messageNumber + LINE_BREAK;
}

/**
 * Helper method to avoid code duplication - allows for prompt input definition
 * @param inputName is used to produce relevant error messages
 * @param maxLengthAllowed is used to check length and throw error if necessary
 * @return
 */
basic_string<char> ClientService::inputLine(const string &inputName, int maxLengthAllowed) {
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

/**
 * processes LOGIN command
 * for password input StdinEcho is turned off
 * @return
 */
std::string ClientService::processLogin() {
    string username = inputLine("Username", USERNAME_MAX_LENGTH);

    setStdinEcho(false);
    string password = inputLine("Password", NO_LIMIT);
    setStdinEcho(true);

    return string(LOGIN) + LINE_BREAK +
           username + LINE_BREAK +
           password + LINE_BREAK;
}

/**
 * Display available options based on whether the user has logged in or not
 */
void ClientService::displayOptions() const {
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

/**
 * Helper method to turn off StdinEcho
 * @param enable
 */
void ClientService::setStdinEcho(bool enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

/**
 * Getter
 * @return
 */
bool ClientService::isLoggedIn() const {
    return loggedIn;
}

/**
 * Setter
 * @param loggedIn
 */
void ClientService::setLoggedIn(bool userLoggedIn) {
    ClientService::loggedIn = userLoggedIn;
}

