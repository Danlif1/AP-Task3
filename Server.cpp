#include "Server.h"

Server::Server(int port, std::vector<Point> classifiedPoints) {
    Server::port = port;
    Server::classifiedPoints = classifiedPoints;
    Server::socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_server < 0) {
        std::cout << "Error creating socket" << std::endl;
        exit(1);
    }
    bindSocket();
}

void Server::bindSocket() {
    memset(&(Server::server_address), 0, sizeof(server_address));
    Server::server_address.sin_family = AF_INET;
    Server::server_address.sin_addr.s_addr = INADDR_ANY;
    Server::server_address.sin_port = htons(port);
    if (bind(socket_server, (struct sockaddr *) &(Server::server_address), sizeof(Server::server_address)) < 0) {
        perror("error binding socket");
    }
}

void Server::connectToClient() {
    if (listen(socket_server, 5) < 0) {
        perror("error listening on socket");
    }
    socklen_t client_len = sizeof(client_address);
    Server::client_sock = accept(Server::socket_server, (struct sockaddr *) &(Server::client_address), &(Server::client_len));
    if (Server::client_sock < 0) {
        perror("error accepting connection");
    }
}

void Server::receiveFromClient() {
    memset(&(Server::buffer), 0, sizeof(Server::buffer));
    int expected_data_len = sizeof(Server::buffer);
    int read_bytes = recv(Server::client_sock, Server::buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        // connection is closed
        // So we need to get the next client.
    } else if (read_bytes < 0) {
        // error
    } else {
        readInput();
    }
}

void Server::readInput() {
    std::vector<double> point;                      // Initializing the point.
    std::string distMetric = "";                    // Initializing the distance metric.
    int k = -1;                                     // Initializing k.
    std::string currentInfo = "";                   // Initializing the info string.
    char* answer;                                   // Initializing the answer.
    std::string bufferString = "";                  // Initializing the buffer string.
    
    // First we will transform the buffer from char* to string.

    for(int i = 0; i < 4096; i++){                  // 4096 is the size of the buffer.
        if(buffer[i] = '\0'){                       // We reached the end of the buffer
            break;
        } else {                                    // There is more to read.
            bufferString += buffer[i];
        }
    }
    
    // Now we will read the entire buffer and we will cut it into a vector a distance metric and a k.
    for(int i = 0; i < bufferString.size(); i++){
        if(bufferString[i] != ' '){                 // We did not get to the end of the current variable yet.
            currentInfo += bufferString[i];
        } else {                                    // We did get to the end of the current variable.
            // We want to check if the current variable is a number or not.
            if (IsDouble(currentInfo)){             // It is a number so it could be either k or a part of the vector.
                if (distMetric != ""){              // We have already initialized the distance metric so the argument is k.
                    if (k != -1){                   // There is an invalid input in the buffer.
                        answer = new char[14];
                        strcpy(answer, "invalid input");
                        break;
                    }
                    k = stod(currentInfo);
                } else {                            // We did not initialize the distance metric yet so the argument is part of the vector.
                    point.push_back(stod(currentInfo));
                }
            } else {                                // The current variable is a string so it should be the distance metric.
                if(distMetric != ""){               // There is an invalid input in the buffer.
                    answer = new char[14];
                    strcpy(answer, "invalid input");
                    break;
                }
                distMetric = currentInfo;
            }
            currentInfo = "";                       // We want to restart the currentInfo after getting the variable to be ready for the next one.
        }
    }
    // After all this we now have a vector, distance metric and a k.
    if(answer[0] == 'i') {
        // There is an error in the information. ('i' is the first letter of invalid input)
       sendToClient(answer);
    } else {
        // There is no error in the information.
        runKNN(point, distMetric, k);
    }
}


void Server::runKNN(Point point, std::string distMetric, int k) {
    if (!PointsCount(k, Server::classifiedPoints.size())){
        //K is either too big or too small, so we need to terminate the program.
        char* answer = new char[14];
        strcpy(answer, "invalid input");
        sendToClient(answer);
    }
    KNN knn_run(k,distMetric);
    knn_run.fit(Server::classifiedPoints);
    if (!GoodVector(point, Server::classifiedPoints[0])){
        if (!point.getAll().empty()) {
            char* answer = new char[14];
            strcpy(answer, "invalid input");
            sendToClient(answer);
        }
    } else {
        std::string result = knn_run.predict(point);    // Getting the result in a string form.
        char* answer = new char[result.length() + 1];   // Resizing answer to fit the string.
        strcpy(answer, result.c_str());
        sendToClient(answer);                           // Setting answer to be the same as result.
    }
}
void Server::sendToClient(char* answer) {
    if (send(Server::client_sock, answer, strlen(answer), 0) < 0) {
        perror("error sending to client");
    }
}

void Server::closeSocket(){
    close(Server::socket_server);
}



