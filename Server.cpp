#include "Server.h"

Server::Server(int port, vector<Point> classifiedPoints) {
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
    if (listen(sock, 5) < 0) {
        perror("error listening on socket");
    }
    socklen_t client_len = sizeof(client_address);
    int client_sock = accept(Server::sock, (struct sockaddr *) &(Server::client_address), &(Server::client_len));
    if (client_sock < 0) {
        perror("error accepting connection");
    }
}

void Server::receiveFromClient() {
    memset(&(Server::buffer), 0, sizeof(Server::buffer));
    int expected_data_len = sizeof(Server::buffer);
    int read_bytes = recv(client_sock, Server::buffer, expected_data_len, 0);
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
    std::string currentInfo = "";                   // Initializing the info string.
    std::string distMetric = "";                    // Initializing the distance metric.
    char* answer;                                   // Initializing the answer.
    int k = 0;                                      // Initializing k.
    bool FinishedReading = true;                    // Starting to read.
    while(FinishedReading){
        for(int i = 0; i < 1024; i++){              // We want to read the entire buffer.
            if (buffer[i] != ' '){                  // If buffer is not space then its part of the same variable.
                currentInfo += buffer[i];           // So we want to continue read it.
            } else {
                if (distMetric == "") {             // Both k and point can have the same type of variable but distMetric differentiate between them
                    if(IsDouble(currentInfo)){      // The currentInfo is a double so its part of the vector.
                        point.push_back(stod(currentInfo));
                    } else {                        // The currentInfo is not a double, so it's the distance metric.
                        distMetric = currentInfo;
                    }
                } else {                            // This should be the k.
                    if(IsDouble(currentInfo)){
                        k = std::stoi(currentInfo);
                    } else{                         // The k is not an int so there is an error with the send function.
                        answer = new char[14];
                        strcpy_s(answer, "invalid input");
                        sendToClient(answer);
                    }
                    FinishedReading = false;        // We read k or there is a problem with the information given.
                }
                currentInfo = "";                   // Restarting currentInfo.
            }
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
}

void Server::runKNN(Point point, std::string distMetric, int k) {
    if (!PointsCount(k, Server::classifiedPoints.size())){
        //K is either too big or too small, so we need to terminate the program.
        answer = new char[14];
        strcpy_s(answer, "invalid input");
        sendToClient(answer);
    }
    KNN knn_run(k,distMetric);
    knn_run.fit(Server::classifiedPoints);
    if (!GoodVector(point, Server::classifiedPoints[0])){
        if (!point.empty()) {
            answer = new char[14];
            strcpy_s(answer, "invalid input");
            sendToClient(answer);
        }
    } else {
        std::string result = knn_run.predict(point);    // Getting the result in a string form.
        answer = new char[result.length() + 1];                     // Resizing answer to fit the string.
        strcpy(answer, result.c_str());
        sendToClient(answer)// Setting answer to be the same as result.
    }
}
void Server::sendToClient(char* answer) {
    if (send(client_sock, answer, strlen(answer), 0) < 0) {
        perror("error sending to client");
    }
}

void Server::closeSocket(){
    close(Server::socket_server);
}