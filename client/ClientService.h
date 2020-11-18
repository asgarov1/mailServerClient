//
// Created by asgarov1 on 11/17/20.
//

#ifndef SOCKETS_CLIENTSERVICE_H
#define SOCKETS_CLIENTSERVICE_H

#define SENDER_MAX_LENGTH 8
#define RECIPIENT_MAX_LENGTH 8
#define TOPIC_MAX_LENGTH 80
#define NO_LIMIT -1
#define LINE_BREAK "\n"
#define MESSAGE_END ".\n"

#include <string>

class ClientService {


public:
    std::string prepareMessage(std::__cxx11::basic_string<char> basicString);

    std::string processSend();

    std::string processList();

    std::string processRead();

    std::string processDel();

    [[nodiscard]] std::basic_string<char> inputLine(const std::string& inputName, int maxLengthAllowed) const;
};


#endif //SOCKETS_CLIENTSERVICE_H
