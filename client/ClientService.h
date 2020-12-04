//
// Created by asgarov1 on 11/17/20.
//

#ifndef SOCKETS_CLIENTSERVICE_H
#define SOCKETS_CLIENTSERVICE_H

#define USERNAME_MAX_LENGTH 8
#define TOPIC_MAX_LENGTH 80
#define NO_LIMIT -1

#include <string>

class ClientService {

public:
    void displayOptions() const;

    [[nodiscard]] bool isLoggedIn() const;

    void setLoggedIn(bool userLoggedIn);

    std::string prepareMessage(const std::__cxx11::basic_string<char>& basicString);

private:
    static std::string processSend();

    static std::string processList();

    static std::string processRead();

    static std::string processDel();

    [[nodiscard]] static std::basic_string<char> inputLine(const std::string &inputName, int maxLengthAllowed) ;

    static std::string processLogin();

    bool loggedIn = false;
};


#endif //SOCKETS_CLIENTSERVICE_H
