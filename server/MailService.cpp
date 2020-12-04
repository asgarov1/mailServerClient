//
// Created by asgarov1 on 11/17/20.
//

#include "MailService.h"

#define OK "OK\n"
#define ERROR "ERR\n"

using namespace std;

/**
 * Processes received message, processing is different based on whether this address have connected
 * If not connected: can only process LOGIN and QUIT
 * If connected: can only process SEND, LIST, READ, DEL and QUIT
 * all other commands will result in ERR message sent back
 * before processing commands checks if username is logged in for it's address
 * (this is necessary so that a logged in user can't use other logged in users usernames)
 * @param receivedMessage
 * @param address
 * @return
 */
std::string MailService::processMessage(const std::basic_string<char> &receivedMessage, const std::string &address) {
    if (receivedMessage.length() < 4) {
        return string(ERROR) + "Wrong format!" + LINE_BREAK;
    }

    string command = receivedMessage.substr(0, 5);
    if (command.find(QUIT) != string::npos) {
        unregisterSocket(address);
        cout << address << " loggeed out." << endl;
        return OK;
    }

    if (!socketIsRegistered(address)) {
        if (command == LOGIN) {
            return processLogin(receivedMessage, address);
        }
    } else if (socketIsRegistered(address)) {
        string username = socketAndUsername.at(address);
        if (command.find(SEND) != string::npos) {
            return processSend(receivedMessage, username);
        } else if (command.find(LIST) != string::npos) {
            return processList(receivedMessage, username);
        } else if (command.find(READ) != string::npos) {
            return processRead(receivedMessage, username);
        } else if (command.find(DEL) != string::npos) {
            return processDel(receivedMessage, username);
        }
    }
    return string(ERROR) + "Unknown command!";
}

/**
 * processes the SEND command
 * checks for the number of lines in message - wrong amount result in wrong format error message
 * mutex is used for the write operation to ensure synchronized access
 * @param receivedMessage
 * @return
 */
std::string MailService::processSend(const std::basic_string<char> &receivedMessage, const std::string& username) {
    if (StringUtil::numberOfOccurrences(receivedMessage, "\n") < 5) {
        return string(ERROR) + "Wrong format!" + LINE_BREAK;
    }

    string receiver = StringUtil::readNthLine(2, receivedMessage);
    string fileName = receiver + ".txt";
    string path = filePath + "/" + fileName;

    mut.lock();
    int endOfFirstLine = (int) receivedMessage.find('\n', 0) + 1;
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

/**
 * processes the LIST command
 * checks for the number of lines in message - wrong amount result in wrong format error message
 * @param receivedMessage
 * @return
 */
std::string MailService::processList(const std::basic_string<char> &receivedMessage, const std::string& username) {
    if (StringUtil::numberOfOccurrences(receivedMessage, "\n") < 1) {
        return string(ERROR) + "Wrong format!" + LINE_BREAK;
    }
    vector<string> topics = findAllTopicsForUser(username);
    string answer = to_string(topics.size()) + LINE_BREAK;
    for (auto &topic : topics) {
        answer += topic + LINE_BREAK;
    }
    return answer;
}

/**
 * processes the READ command
 * checks for the number of lines in message - wrong amount result in wrong format error message
 * checks that passed in message number is a number, else error message is sent back
 * if such message doesn't exist ERR message is returned
 * @param receivedMessage
 * @return
 */
std::string MailService::processRead(const std::basic_string<char> &receivedMessage, const std::string& username) {
    if (StringUtil::numberOfOccurrences(receivedMessage, "\n") < 2) {
        return string(ERROR) + "Wrong format!" + LINE_BREAK;
    }

    string messageFileText = StringUtil::readFile(getPathForUsername(username));
    if (messageFileText.length() < 1) {
        return ERROR;
    }

    string messageNumberText = StringUtil::readNthLine(2, receivedMessage);
    if (!StringUtil::isNumber(messageNumberText)) {
        return string(ERROR) + "Message number must be a number!" + LINE_BREAK;
    }

    int messageNumber = stoi(messageNumberText) - 1; // -1 because computers count from 0
    vector<string> messages = StringUtil::splitText(messageFileText, "\n\n");

    if (messageNumber < 0 || messageNumber >= messages.size()) {
        return ERROR;
    }

    return OK + messages.at(messageNumber);
}

/**
 * processes the DEL command
 * checks for the number of lines in message - wrong amount result in wrong format error message
 * checks that passed in message number is a number, else error message is sent back
 * if such message doesn't exist ERR message is returned
 * mutex is used for delete operation
 * @param receivedMessage
 * @return
 */
std::string MailService::processDel(const std::basic_string<char> &receivedMessage, const std::string& username) {
    if (StringUtil::numberOfOccurrences(receivedMessage, "\n") < 2) {
        return string(ERROR) + "Wrong format!" + LINE_BREAK;
    }

    string messageFileText = StringUtil::readFile(getPathForUsername(username));

    string messageNumberText = StringUtil::readNthLine(2, receivedMessage);
    if (!StringUtil::isNumber(messageNumberText)) {
        return string(ERROR) + "Message number must be a number!" + LINE_BREAK;
    }
    int messageNumber = stoi(messageNumberText) - 1;
    vector<string> messages = StringUtil::splitText(messageFileText, "\n\n");

    if (messageNumber < 0 || messageNumber >= messages.size()) {
        return ERROR;
    }
    messages.at(messageNumber) = "";

    mut.lock();
    ofstream myFile;
    myFile.open(getPathForUsername(username));
    myFile << StringUtil::flattenToStringWithDelimiter(messages, "\n\n");
    myFile.close();
    mut.unlock();
    return OK;
}


/**
 * helper method is used to list all topics needed for LIST operation
 * @param username
 * @return
 */
vector<string> MailService::findAllTopicsForUser(const std::string &username) {
    std::vector<std::string> topics;
    string messageFileText = StringUtil::readFile(getPathForUsername(username));
    if (messageFileText.length() < 1) {
        return topics;
    }

    vector<string> messages = StringUtil::splitText(messageFileText, "\n\n");
    topics.reserve(messages.size());
    for (auto &message : messages) {
        topics.push_back(StringUtil::readNthLine(2, message));
    }
    return topics;
}

/**
 * helper method gets path for username ([provided_at_start_filePath]/[username].txt)
 * @param username
 * @return
 */
string MailService::getPathForUsername(const string &username) { return filePath + "/" + username + ".txt"; }

/**
 * Constructor
 * initializes filePath for mail folder
 * @param filePath
 */
MailService::MailService(string filePath) : filePath(std::move(filePath)) {}

/**
 * Processes LOGIN
 * checks if this address is in blocked list
 * if it is blocked returns error and amount of minutes and seconds left for block
 * if credentials provided are invalid number of filed for the address gets increment, at 3 user gets blocked for 30 mins
 * @param receivedMessage
 * @param address
 * @return
 */
std::string MailService::processLogin(const std::basic_string<char> &receivedMessage, const std::string &address) {
    if (StringUtil::numberOfOccurrences(receivedMessage, "\n") < 3) {
        return string(ERROR) + "Wrong format!" + LINE_BREAK;
    }
    if (socketsBlocked.contains(address)) {
        double secondsPassed = getSecondsPassed(address);
        if (secondsPassed > TIME_BLOCKED_IN_SECONDS) {
            socketsBlocked.erase(address);
        } else {
            int minutesLeft = (int)(TIME_BLOCKED_IN_SECONDS - secondsPassed) / 60;
            int secondsLeft = ((int) (TIME_BLOCKED_IN_SECONDS - secondsPassed)) % 60;
            return string(ERROR) + "Your client is blocked for " + to_string(minutesLeft) + " minutes and "
                   + to_string(secondsLeft) + " seconds!" + LINE_BREAK;
        }
    }

    string username = StringUtil::readNthLine(2, receivedMessage);
    string password = StringUtil::readNthLine(3, receivedMessage);

    if (LoginService::validateCredentials(username, password)) {
        socketAndUsername[address] = username;
        return OK;
    } else {
        if (!socketFailedLogins.contains(address)) {
            socketFailedLogins[address] = 0;
        }
        socketFailedLogins[address] = socketFailedLogins.at(address) + 1;
        if (socketFailedLogins.at(address) == ALLOWED_ATTEMPTS) {
            socketFailedLogins[address] = 0;
            socketsBlocked[address] = chrono::high_resolution_clock::now();
            return string(ERROR) +
                   "You have failed 3 times! Your client is blocked for 30 mins" + LINE_BREAK;
        }
        return string(ERROR) +
               "Invalid credentials! You have " + to_string(ALLOWED_ATTEMPTS - socketFailedLogins.at(address)) +
               " attempts left." + LINE_BREAK;
    }
}

/**
 * Helper method gets seconds passed between current login attempt for the address and start of block
 * @param address
 * @return
 */
double MailService::getSecondsPassed(const string &address) {
    return (chrono::duration_cast<chrono::duration<double>>(
            std::chrono::high_resolution_clock::now() - socketsBlocked.at(address))).count();
}

/**
 * unregisters (logs out) the client
 * @param address
 */
void MailService::unregisterSocket(const std::string &address) {
    socketAndUsername.erase(address);
}

/**
 * checks if this ip and port is registered at all
 * @param ipAndPort
 * @return
 */
bool MailService::socketIsRegistered(const string &ipAndPort) {
    return socketAndUsername.contains(ipAndPort);
}
