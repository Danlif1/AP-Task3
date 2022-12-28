
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


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
    char data_addr[] = "Im a message from client";
    int data_len = strlen(data_addr);
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
        std::cout << "server disconnected" << std::endl;
    }else {
        std::cout << buffer << std::endl;
    }
    close(client_socket);

    return 0;


}