//
// Created by asgarov1 on 11/17/20.
//

#include "MailService.h"
#include "Command.h"

std::string MailService::processMessage(std::__cxx11::basic_string<char> receivedMessage) {
    if(!receivedMessage.compare(SEND)){
        return processSend();
    } else if(!command.compare(LIST)){
        return processList();
    } else if(!command.compare(READ)){
        return processRead();
    } else if (!command.compare(DEL)){
        return processDel();
    } else {
        return "";
    }

    return std::string();
}

std::string MailService::processSend() {
    return std::string();
}
