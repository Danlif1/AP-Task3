
#ifndef AP_TASK2_KNN_H
#define AP_TASK2_KNN_H

#include <tuple>
#include <algorithm>
#include "CalcDist.h"



class KNN {
    int k;

    std::string distance_metric;
    std::vector<Point> data;

    std::vector<std::tuple<double, std::string>> distance(std::vector<double> a);

    std::string nearestNeighbor(std::vector<std::tuple<double, std::string>> distances) const;


public:
    KNN(int k, std::string metric);

    void fit(std::vector<Point> classified_point);

    std::string predict(Point newpoint);
};
#endif //AP_TASK2_KNN_H
