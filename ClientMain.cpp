//
// Created by lenovo on 1/2/2023.
//
#include "Client.h"
#include "ClientInputCheck.h"

int main(int argc, char **argv) {
    // check that argc is 3
    // check that argv[1] is a valid IP address
    // check that argv[2] is a valid port number
    if (!inputCheck(argc, argv)) {
        std::perror("Invalid input");
        return 0;
    }
    Client client(atoi(argv[2]), argv[1]);
    client.connectToServer();
    while (client.receiveInput()) {
        client.receiveFromServer();
    }
//    delete &client;
    return 0;
}
