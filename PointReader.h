//
// Created by Daniel Lifshitz on 30/11/2022.
//


#ifndef AP_TASK2_POINTREADER_H
#define AP_TASK2_POINTREADER_H
#include "SafetyChecks.h"
class PointReader {
private:
    std::string fileName;
    std::ifstream fin;
    std::vector<std::string> row;


public:
    PointReader(const std::string&);
    bool getNextPoint(Point&);

};
#endif //AP_TASK2_POINTREADER_H
