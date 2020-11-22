#include "ClientSocket.h"
#include "../SocketException.h"
#include "ClientService.h"
#include "../Command.h"
#include "../exception/IllegalMessageFormatException.h"
#include "../exception/IllegalCommandException.h"
#include <iostream>
#include <string>

static const char *const SEPERATION_CHARACTER = " | ";

void displayOptions();

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

        while (input.compare("QUIT") != 0) {
            displayOptions();
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
            std::cout << reply <<endl;
        }
    }
    catch (SocketException &e) {
        std::cout << "Exception was caught: " << e.description() << "\n";
    }
    return 0;
}

void displayOptions() {
    cout << "Available commands are: " +
            string(SEND) + SEPERATION_CHARACTER +
            LIST + SEPERATION_CHARACTER +
            READ + SEPERATION_CHARACTER +
            DEL + SEPERATION_CHARACTER +
            QUIT << endl;
}
