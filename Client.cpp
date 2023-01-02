
#include "ClientInputCheck.h"
#include "Client.h"

Client::Client(int port, char *ip) {
    Client::port = port;
    Client::ip = ip;
    Client::client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (Client::client_socket < 0) {
        std::perror("error creating socket");
    }
    memset(&(Client::remote_address), 0, sizeof(Client::remote_address));
    Client::remote_address.sin_family = AF_INET;
    Client::remote_address.sin_addr.s_addr = inet_addr(Client::ip);
    Client::remote_address.sin_port = htons(Client::port);
}


void Client::connectToServer() {
    if (connect(Client::client_socket,(struct sockaddr *) &(Client::remote_address), sizeof(Client::remote_address)) < 0) {
        std::perror("error connecting to server");
    }

}

void Client::sendToServer(std::string input) {
    int data_len = input.size() + 1;
    // sending data to the server
    int sent_bytes = send(client_socket, input.c_str(), data_len, 0);
    if (sent_bytes < 0) {
        std::perror("error sending message");
    }
}

bool Client::receiveInput() {
    std::string input;
    std::getline(std::cin, input);
    if (input == "-1") {
        closeSocket();
        return false;
    } else {
        Client::sendToServer(input);
        return true;
    }
}

void Client::closeSocket() {
    close(Client::client_socket);
}

void Client::receiveFromServer() {
    memset(Client::buffer, 0, sizeof(Client::buffer));
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(Client::client_socket, buffer, expected_data_len, 0);
    if (read_bytes < 0) {
        std::perror("error reading from socket");
    } else if (read_bytes == 0) {
        // if connection to server is closed we end the program
        std::perror("server disconnected");
    } else {
        std::cout << buffer << std::endl;
    }
}
