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

bool Server::receiveFromClient() {
    memset(&(Server::buffer), 0, sizeof(Server::buffer));
    int expected_data_len = sizeof(Server::buffer);
    int read_bytes = recv(Server::client_sock, Server::buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        // connection is closed
        // So we need to get the next client.
        return false;
    } else if (read_bytes < 0) {
        // error
        perror("error reading bytes");
        return false;
    } else {
        readInput();
        return true;
    }
}

void Server::readInput() {
    std::vector<double> point;                      // Initializing the point.
    std::string distMetric = "";                    // Initializing the distance metric.
    int k = -1;                                     // Initializing k.
    std::string currentInfo = "";                   // Initializing the info string.
    char* answer;                                   // Initializing the answer.
    std::string bufferString = "";                  // Initializing the buffer string.
    bool inVector = true;                           // Initializing the inVector boolean.
    bool error = false;                             // Initializing the error boolean.
    // First we will transform the buffer from char* to string.

    for(int i = 0; i < 4096; i++){                  // 4096 is the size of the buffer.
        if(buffer[i] == '\0'){                       // We reached the end of the buffer
            break;
        } else {                                    // There is more to read.
            bufferString += buffer[i];
        }
    }
    std::stringstream bufferStream(bufferString);
    // Now we will read the entire buffer and we will cut it into a vector a distance metric and a k.
    while (std::getline(bufferStream, currentInfo, ' ')) {
        if(inVector){
            if(IsDouble(currentInfo)){
                point.push_back(stod(currentInfo));
            } else {
                distMetric = currentInfo;
                inVector = false;
            }
        } else {
            if(IsDouble(currentInfo)){
                k = stod(currentInfo);
            } else {
                error = true;
            }
        }
    }
    if (k == -1){
        error = true;
    }
    if(error) {
        // There is an error in the information. ('i' is the first letter of invalid input)
        char invInp[14] = "invalid input";
       sendToClient(invInp);
    } else {
        // There is no error in the information.
        runKNN(point, distMetric, k);
    }
}


void Server::runKNN(Point point, std::string distMetric, int k) {
    if (!PointsCount(k, Server::classifiedPoints.size())){
        //K is either too big or too small, so we need to terminate the program.
        char* answer = new char[20];
        memset(answer, '\0', 20);
        strcpy(answer, "invalid input");
        sendToClient(answer);
    }
    KNN knn_run(k,distMetric);
    knn_run.fit(Server::classifiedPoints);
    if (!GoodVector(point, Server::classifiedPoints[0])){
        if (!point.getAll().empty()) {
            char* answer = new char[20];
            memset(answer, '\0', 20);
            strcpy(answer, "invalid input");
            sendToClient(answer);
        }
    } else {
        std::string result = knn_run.predict(point);    // Getting the result in a string form.
        char* answer = new char[result.length() + 1];   // Resizing answer to fit the string.
        memset(answer, '\0', result.length() + 1);
        strcpy(answer, result.c_str());
        sendToClient(answer);                           // Setting answer to be the same as result.
    }
}
void Server::sendToClient(char* answer) {
    std::cout << answer << std::endl;
    if (send(Server::client_sock, answer, strlen(answer), 0) < 0) {
        perror("error sending to client");
    }
}

void Server::closeSocket(){
    close(Server::socket_server);
}



