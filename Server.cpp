// Server side C/C++ program to demonstrate Socket
// programming
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


/**
 * @brief The main function of the server
 * 
 * @param argc Should have file and port by that order.
 * @param argv Should be 3.
 * @return int Returning 0 if there is a problem with the inputs.
 */
int main(int argc, char const* argv[])
{
    if(argc != 3) {
        std::cout << "Please enter both file and port into argv" << std::endl;
        return 0;
    }
    std::fstream fout;
    std::string fileName = argv[1];
    if (!CheckFile(fileName)) {
        //The file doesn't end with .csv, so we need to terminate the program.
        std::cout << "The file doesn't end with .csv" << std::endl;
        return 0;
    } else {
        // Opening the file.
        fout.open(fileName, std::ios::out | std::ios::app);
    }
    PointReader classifiedPointReader(fileName);
    Point cPoint;
    std::vector<Point> classifiedPoints;
    //creating an array of classified points.
    while (classifiedPointReader.getNextPoint(cPoint)) { classifiedPoints.push_back(cPoint); }
    if(!IsSameSize(classifiedPoints)){
        std::cout << "Not all vectors are valid, please use a different file." << std::endl;
        return 0;
    }


    // Taken from Introduction to Computer Networks
    const int port = atoi(argv[2]);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);
    if (bind(sock,(struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    while (true){
        if (listen(sock, 5) < 0) {
            perror("error listening to a socket");
        }
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr*)&client_sin, &addr_len);
        if (client_sock < 0) {
            perror("error accepting client");
        }
        while (true) {
            char buffer[4096];
            int expected_data_len = sizeof(buffer);
            int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
            if (read_bytes == 0) {
                // connection is closed 
                // So we need to get the next client.
                break;
            } else if (read_bytes < 0) {
                // error 
            } else {
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
                                    strcpy(answer, "invalid input");
                                }
                                FinishedReading = false;        // We read k or there is a problem with the information given.
                            }
                            currentInfo = "";                   // Restarting currentInfo.
                        }
                    }
                }
                // After all this we now have a vector, distance metric and a k.
                if(answer[0] == 'i') {                      // There is an error in the information. ('i' is the first letter of invalid input)
                    send(client_sock, answer, strlen(answer), 0);
                } else {
                    if (!PointsCount(k, classifiedPoints.size())){
                        //K is either too big or too small, so we need to terminate the program.
                        answer = new char[14];
                        strcpy(answer, "invalid input");
                        send(client_sock, answer, strlen(answer), 0);
                    }
                    KNN knn_run(k,distMetric);
                    knn_run.fit(classifiedPoints);
                    if (!GoodVector(point, classifiedPoints[0])){
                        if (!point.empty()) {
                            answer = new char[14];
                            strcpy(answer, "invalid input");
                            send(client_sock, answer, strlen(answer), 0);
                        }
                    } else {
                        std::string result = knn_run.predict(point);    // Getting the result in a string form.
                        answer = new char[result.length() + 1];                     // Resizing answer to fit the string. 
                        strcpy(answer, result.c_str());                             // Setting answer to be the same as result.
                        send(client_sock, answer, read_bytes, 0);
                        int sent_bytes = send(client_sock, buffer, read_bytes, 0);  // Sending the answer.
                        if (sent_bytes < 0) {
                            perror("error sending to client");
                        }
                    }
                }
            }
            
        }
    }
    // we won't get here because it's while(true), but we still want to remember we need to close the socket at the end of the code.
    close(sock);

	return 0;
    
}
