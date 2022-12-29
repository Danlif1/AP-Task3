
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include "SafetyChecks.h"


int main(int argc, char **argv) {
    const char* ip = argv[1];
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
    //flag for while loop
    bool run = true;
    //received input from user
    std::string input;
    std::getline(std::cin, input);
    while (run) {
        // declaring character array (+1 for null terminator)
        char* data_addr = new char[input.length() + 1];
        // copying the contents of the input to char array to be sent to server
        std::strcpy(data_addr, input.c_str());
        int data_len = strlen(data_addr);
        // sending data to the server
        int sent_bytes = send(client_socket, data_addr, data_len, 0);
        if (sent_bytes < 0) {
            std::perror("error sending message");
        }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(client_socket, buffer, expected_data_len, 0);
        if (read_bytes < 0) {
            std::perror("error reading from socket");
        }else if (read_bytes == 0) {
            // if connection to server is closed we end the program
            std::cout << "server disconnected" << std::endl;
            run = false;
        }else {
            std::cout << buffer << std::endl;
        }
        //prepare to receive new input from user
        input.clear();
        delete[] data_addr;
        std::getline(std::cin, input);
        if (input == "-1") {
            run = false;
        }
    }
    close(client_socket);

    return 0;


}