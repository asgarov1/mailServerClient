#include "ClientSocket.h"
#include "../SocketException.h"
#include "ClientService.h"
#include <iostream>
#include <string>

using namespace std;

void errNDie(const char *message) {
    fprintf(stderr, "%s", message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        errNDie("usage: client [ip address] [port number]\n");
    }

    ClientService clientService;

    try {
        ClientSocket clientSocket(argv[1], stoi(argv[2]));

        string reply;
        string input;

        while (getline(cin, input) && input.compare("QUIT") != 0) {

            string message = clientService.prepareMessage(input);

            clientSocket << input;
            clientSocket >> reply;
            std::cout << "Server's reply: \"" << reply << "\"\n";;
        }
    }
    catch (SocketException &e) {
        std::cout << "Exception was caught:" << e.description() << "\n";
    }

    return 0;
}