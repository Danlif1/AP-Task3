//
// Created by lenovo on 1/2/2023.
//

#ifndef UNTITLED_SERVER_H
#define UNTITLED_SERVER_H

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include "SafetyChecks.h"
#include "Point.h"
#include "PointReader.h"
#include "KNN.h"
#include "SafetyChecks.h"



class Server {
    const int port;
    int socket_server;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    unsigned int client_len = sizeof(client_address);
    char buffer[4096];
    vector<Point> classifiedPoints;

    void sendToClient(std::string);
    void bindSocket();
    void runKNN(std::string);

public:
    Server(int, vector<Point>);
    void connectToClient();
    void receiveFromClient();
    void closeSocket();


};




#endif //UNTITLED_SERVER_H
