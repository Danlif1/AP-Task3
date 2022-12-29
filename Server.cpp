// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
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
        //The file doesn't end with .csv so we need to terminate the program.
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
    const int port = atoi(argv[2]);


    // Taken from https://www.geeksforgeeks.org/socket-programming-cc/
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = { 0 };
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket
		= accept(server_fd, (struct sockaddr*)&address,
				(socklen_t*)&addrlen))
		< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
    

    while(true) {
        std::vector<double> point;                      // Initilizing the point.
        std::string currentInfo = "";                   // Initilizing the info string.
        std::string distMetric = "";                    // Initilizing the distance metric.
        char* answer;                                   // Initilzing the answer.
        int k = 0;                                      // Initilzing k.
        bool FinishedReading = true;                    // Starting to read.
        while(FinishedReading){
            valread = read(new_socket, buffer, 1024);   // Reading the first 1024 bits of data.
            for(int i = 0; i < 1024; i++){              // We want to read the entire buffer.
                if (buffer[i] != ' '){                  // If buffer is not space then its part of the same variable.
                    currentInfo += buffer[i];           // So we want to continue read it.
                } else {
                    if (distMetric == "") {             // Both k and point can have the same type of variable but distMetric differentiate between them
                        if(IsDouble(currentInfo)){      // The currentInfo is a double so its part of the vector.
                            point.push_back(stod(currentInfo));
                        } else {                        // The currentInfo is not a double so its the distance metric.
                            distMetric = currentInfo;
                        }
                    } else {                            // This should be the k.
                        if(IsDouble(currentInfo)){
                            k = std::stoi(currentInfo);
                        } else{                         // The k is not an int so there is an error with the send.
                            answer = "Please enter a different k this one is not an int.";
                        }
                        FinishedReading = false;        // We read k or there is a problem with the information given.
                    }
                    currentInfo = "";                   // Restarting currentInfo.
                }
            }
        }
        // After all this we now have a vector, distance metric and a k.
        if(answer[0] == 'P') {                      // There is an error in the information.
            send(new_socket, answer, strlen(answer), 0);
        } else {
            if (!PointsCount(k, classifiedPoints.size())){
                //K is either too big or too small so we need to terminate the program.
                return 0;
            }
            KNN knn_run(k,distMetric);
            knn_run.fit(classifiedPoints);
            if (!GoodVector(point, classifiedPoints[0])){
                if (!point.empty()) {
                    std::cout << "Please enter the correct number of arguments into the vector." << std::endl;
                }
            } else {
                std::string result = knn_run.predict(point);    // Getting the result in a string form.
                answer = new char[result.length() + 1];         // Resizing answer to fit the string. 
                strcpy(answer, result.c_str());                 // Setting answer to be the same as result.
                send(new_socket, answer, strlen(answer), 0);    // Sending the answer.
            }
        }
    }


    // We won't get here ever but we still want to be able to close the socket with just changing the while parameter.
	// closing the connected socket
	close(new_socket);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}
