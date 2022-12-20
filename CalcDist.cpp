#include "CalcDist.h"

/**
 * @brief Calculating the distance of two vectors using Minkowski distance.
 *
 * @param point1 First vector.
 * @param point2 Second vector.
 * @param power The power with which we use in the function as its (|p1[i]-p2[i]|)^p.
 * @return double The distance between two vectors.
 */
double Minkowski(std::vector<double> point1, std::vector<double> point2, int power) {
    double result = 0;
    for (int i = 0; i < point1.size(); i++) {

        result += (double) pow(abs((double) point1[i] - (double) point2[i]), power);
    }
    result = pow(result, 1.0 / power);
    return result;
}


/**
 * @brief Calculating the distance of two vectors using Euclidian distance.
 * Actually just calling Minkowski with 2 as it does the same thing.
 * 
 * @param point1 First vector.
 * @param point2 Second vector.
 * @return double The distance between two vectors.
 */
double Euclidan(std::vector<double> point1, std::vector<double> point2) {
    return Minkowski(point1, point2, 2);
}

/**
 * @brief Calculating the distance of two vectors using Manhattan distance.
 * Actually just calling Minkowski with 1 as it does the same thing.
 * 
 * @param point1 First vector.
 * @param point2 Second vector.
 * @return double The distance between two vectors.
 */
double Manhattan(std::vector<double> point1, std::vector<double> point2) {
    return Minkowski(point1, point2, 1);
}

/**
 * @brief Calculating the distance of two vectors using Chebyshev distance.
 * 
 * @param point1 First vector.
 * @param point2 Second vector.
 * @return double The distance between two vectors.
 */
double Chebyshev(std::vector<double> point1, std::vector<double> point2) {
    double result = 0;
    for (int i = 0; i < point1.size(); i++) {
        if (result < (double) abs((double) point1[i] - (double) point2[i])) {
            result = (double) abs((double) point1[i] - (double) point2[i]);
        }
    }
    return result;
}

/**
 * @brief Calculating the distance of two vectors using Canberra distance.
 * 
 * @param point1 First vector.
 * @param point2 Second vector.
 * @return double The distance between two vectors.
 */
double Canberra(std::vector<double> point1, std::vector<double> point2) {
    double result = 0;
    for (int i = 0; i < point1.size(); i++) {
        result += (double) abs((double) point1[i] - (double) point2[i]) /
                  (abs((double) point1[i]) + abs((double) point2[i]));
    }
    return result;
}


/**
 * Calculating the distance between two points using the distance metric given.
 * @param metric The distance metric.
 * @param uPoint The first point.
 * @param kPoint The second point.
 * @return The distance.
 */
double calcDistance(std::string metric, std::vector<double> uPoint, Point kPoint) {
    //A distance metric is given by 3 letters.
    for (int i = 0; i < 3; i++) {
        metric[i] = std::toupper(metric[i]);
    }
    int isEqual = metric.compare("AUC");
    if (!isEqual) {
        //Meaning its AUC.
        return Euclidan(uPoint, kPoint.getAll());
    }
    isEqual = metric.compare("MAN");
    if (!isEqual) {
        //Meaning its MAN.
        return Manhattan(uPoint, kPoint.getAll());
    }
    isEqual = metric.compare("CHB");
    if (!isEqual) {
        //Meaning its CHB.
        return Chebyshev(uPoint, kPoint.getAll());
    }
    isEqual = metric.compare("CAN");
    if (!isEqual) {
        //Meaning its CAN.
        return Canberra(uPoint, kPoint.getAll());
    }
    isEqual = metric.compare("MIN");
    if (!isEqual) {
        //Meaning its MIN.
        return Minkowski(uPoint, kPoint.getAll(), 2);
    }
}
