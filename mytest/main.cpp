#include "../server/MailService.h"

int main(int argc, char *argv[]) {
    MailService mailService("/home/asgarov1/mail");

    std::string message = "SEND\n"
                     "if19b003\n"
                     "if19b002\n"
                     "some topic\n"
                     "Hey there kinda missed you wanted to ask whats up?\n"
                     ".\n";

    mailService.processSend(message);

    return 0;
}