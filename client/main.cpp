#include "ClientSocket.h"
#include "ClientService.h"
#include "../shared/socket/SocketException.h"
#include "../shared/exception/IllegalMessageFormatException.h"
#include "../shared/exception/IllegalCommandException.h"
#include "../shared/util/StringUtil.h"
#include "../shared/Command.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "usage: mailclient [ip address] [port number]" << endl;
        exit(EXIT_FAILURE);
    }

    ClientService clientService;
    try {
        ClientSocket clientSocket(argv[1], stoi(argv[2]));

        string reply;
        string input;

        while (input != QUIT) {
            clientService.displayOptions();
            string message;
            try {
                getline(cin, input);
                message = clientService.prepareMessage(input);
            } catch (IllegalMessageFormatException &e) {
                cout << e.description() << endl;
                continue;
            } catch (IllegalCommandException &e) {
                cout << e.description() << endl;
                continue;
            }
            clientSocket << message;
            clientSocket >> reply;
            if (!clientService.isLoggedIn() && reply == "OK\n") {
                clientService.setLoggedIn(true);
            }
            std::cout << reply << endl;
        }
    }
    catch (SocketException &e) {
        std::cout << "Exception was caught: " << e.description() << "\n";
    }
    return 0;
}