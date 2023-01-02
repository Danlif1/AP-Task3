//
// Created by lenovo on 1/2/2023.
//

#ifndef UNTITLED_CLIENT_H
#define UNTITLED_CLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>

class Client {
    int port;
    const char *ip;
    static int client_socket;
    static struct sockaddr_in remote_address;
    char buffer[4096];

    void sendToServer(std::string input);
    void closeSocket();

public:
    Client(int port, char *ip);
    void connectToServer();
    bool receiveInput();
    void receiveFromServer();


};


#endif //UNTITLED_CLIENT_H
