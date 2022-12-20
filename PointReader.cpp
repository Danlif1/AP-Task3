//
// Created by Daniel Lifshitz on 30/11/2022.
//

#include "PointReader.h"

/**
 * @brief Iris will be represented as points in space as it is the same and could be minimally changed to fit other descriptions.
 * This comment will be moved afterwards to the Point file.
 */
/**
 * @brief Finding the file we read from and opening him.
 * The error message is given if the file with that name doesn't exist or the name isn't that of a file.
 *
 * @param fileName The name of the file we want to read from.
 */
PointReader::PointReader(const std::string& fileName) {
    this->fileName = fileName;
    fin.open(fileName);
    if(!fin.is_open()) {
        //Error Message
        std::cout<< "Could not open the file " << fileName << std::endl;
        std::cout<<"Error code: " << strerror(errno) << std::endl;
    }


}

/**
 * @brief Reading a line and initializing a point from the given line.
 *
 * @param point The point we initialize.
 * @return Returning true if there is another line to read from, and false otherwise.
 */
bool PointReader::getNextPoint(Point& point) {
    row.clear(); // clear the vector
    std::string line, word;
    if (getline(fin, line)) {
        std::stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        point.setFromVector(row);
        return true;
    }
    return false;
}
