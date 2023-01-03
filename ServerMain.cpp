// Server side C/C++ program to demonstrate Socket
// programming
#include <stdlib.h>
#include <string.h>
#include "PointReader.h"
#include "Server.h"


/**
 * @brief The main function of the server
 * 
 * @param argc Should have file and port by that order.
 * @param argv Should be 3.
 * @return int Returning 0 if there is a problem with the inputs.
 */
int main(int argc, char const* argv[]) {
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
    Server server(atoi(argv[2]),classifiedPoints);
    while(true) {
        server.connectToClient();
        while (server.receiveFromClient()) {}
    }
    server.closeSocket();
    delete &server;
    return 0;
}
