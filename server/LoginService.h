//
// Created by asgarov1 on 11/22/2020.
//

#ifndef SOCKETS_LOGINSERVICE_H
#define SOCKETS_LOGINSERVICE_H


class LoginService {
public:
    static bool validateCredentials(const std::string& username, const std::string& password);
};


#endif //SOCKETS_LOGINSERVICE_H
