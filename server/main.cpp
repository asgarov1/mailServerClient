#include "ServerSocket.h"
#include "../SocketException.h"
#include "MailService.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "Ready for connections....\n";

    MailService mailService("/home/asgarov1/mail");

    try {
        ServerSocket server(8000);

        while (true) {
            ServerSocket newSocket;
            server.accept(newSocket);
            while (true) {
                std::string receivedMessage;
                newSocket >> receivedMessage;
                std::cout << "SERVER RECEIVED:\n" << receivedMessage << std::endl;
                string answer = mailService.processMessage(receivedMessage);
                newSocket << answer;
            }
        }
    }
    catch (SocketException &e) {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

    return 0;
}