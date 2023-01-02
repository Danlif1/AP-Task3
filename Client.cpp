
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include "ClientInputCheck.h"



int main(int argc, char **argv) {
    // check that argc is 3
    // check that argv[1] is a valid IP address
    // check that argv[2] is a valid port number
    if (!inputCheck(argc, argv)) {
        std::perror("Invalid input");
    }
    const char *ip = argv[1];
    const int port = atoi(argv[2]);
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        std::perror("error creating socket");
    }
    struct sockaddr_in remote_address;
    memset(&remote_address, 0, sizeof(remote_address));
    remote_address.sin_family = AF_INET;
    remote_address.sin_addr.s_addr = inet_addr(ip);
    remote_address.sin_port = htons(port);
    if (connect(client_socket, (struct sockaddr *) &remote_address, sizeof(remote_address)) < 0) {
        std::perror("error connecting to server");
    }


    while (true) {
        //received input from user
        std::string input;
        std::getline(std::cin, input);
        //check if we need to close the connection
        if (input == "-1") {
            break;
        }
        int data_len = input.size() + 1;
        // sending data to the server
        int sent_bytes = send(client_socket, input.c_str(), data_len, 0);
        if (sent_bytes < 0) {
            std::perror("error sending message");
        }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(client_socket, buffer, expected_data_len, 0);
        if (read_bytes < 0) {
            std::perror("error reading from socket");
        } else if (read_bytes == 0) {
            // if connection to server is closed we end the program
            std::perror("server disconnected");
        } else {
            std::cout << buffer << std::endl;
        }

    }
    close(client_socket);

    return 0;
}