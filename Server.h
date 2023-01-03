//
// Created by lenovo on 1/2/2023.
//

#ifndef AP_TASK3_SERVER_H
#define AP_TASK3_SERVER_H

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


class Server {
    int port;
    int socket_server;
    int client_sock;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    unsigned int client_len = sizeof(client_address);
    char buffer[4096];
    std::vector<Point> classifiedPoints;

    void sendToClient(char*);
    void bindSocket();
    void runKNN(Point ,std::string, int);

public:
    Server(int, std::vector<Point>);
    void connectToClient();
    void receiveFromClient();
    void closeSocket();
    void readInput();

};




#endif //AP_TASK3_SERVER_H
