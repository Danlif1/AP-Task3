//
// Created by Daniel Lifshitz on 30/11/2022.
//

#ifndef AP_TASK2_SAFETYCHECKS_H
#define AP_TASK2_SAFETYCHECKS_H

#include "Point.h"
bool NumberOfArguments(int);
bool PointsCount(long, long);
bool KCheck(std::string);
bool IsSameSize(std::vector<Point>);
bool GoodVector(Point, Point);
bool CheckFile (std::string const &);
bool CheckMetric(std::string);
#endif //AP_TASK2_SAFETYCHECKS_H