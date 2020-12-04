#include "ServerSocket.h"
#include "../shared/socket/SocketException.h"
#include "MailService.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "Ready for connections..." << endl;
    if (argc < 3) {
        cerr << "usage: mailserver [port] [path to mail folder]" << endl;
        exit(EXIT_FAILURE);
    }

    if (!StringUtil::isNumber(argv[1]) || stoi(argv[1]) < 1024 || stoi(argv[1]) > 49151) {
        cerr << "port must be a number between 1024 and 49151!" << endl;
        exit(EXIT_FAILURE);
    }

    mkdir(argv[2], 0777);
    if (!filesystem::exists(argv[2])) {
        cerr << "Problem creating the provided path to mail folder!" << endl;
        exit(EXIT_FAILURE);
    }

    MailService mailService(argv[2]);
    try {
        ServerSocket server(stoi(argv[1]));

        while (true) {
            ServerSocket newSocket;
            std::string clientIpAndPort = server.accept(newSocket);
            cout << "New client: " << clientIpAndPort << endl;
            pid_t pid = fork();
            if (pid == 0) {
                std::string receivedMessage;
                while (receivedMessage != QUIT) {
                    newSocket >> receivedMessage;
                    string answer = mailService.processMessage(receivedMessage, clientIpAndPort);
                    newSocket << answer;
                }
                exit(0);
            }

        }
    }
    catch (SocketException &e) {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

    return 0;
}