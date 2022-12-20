
#include "KNN.h"

/**
 * Constructor
 * @param k The number of neighbours we want to find.
 * @param metric The distance metric we want to use.
 */
KNN::KNN(int k, std::string metric) {
    KNN::k = k;
    KNN::distance_metric = metric;
}

//point might not need to be a class of its own, if it is it's only to separate the vector from the label
/**
 * Fits the training data to the knn object. training data consists of data(x) and labels(y).
 * @param classified_points Vector that contains classified data.
 */
void KNN::fit(std::vector<Point> classified_points) {
    //need to decide if we store the data as to separate arrays. might be better to utilize the class point.
    //if we decide to not separate them we need to take care of functions in distance method.
    KNN::data = classified_points;
}

/**
 * Predicts the label of a given unclassified vector.
 * @return The label of the point.
 */
std::string KNN::predict(Point newpoint) {
    std::vector<std::tuple<double, std::string>> dis_from_point = distance(newpoint.getAll());
    std::string label = nearestNeighbor(dis_from_point);
    return label;
}

/**
 * Calculates the distance from the unclassified vector, to the classified data we have.
 * @param a The unclassified information.
 * @return A vector of tuples (the tuple will consist of the distance and the classified label) with the distance of the unclassified data from the classified vector.
 */
std::vector<std::tuple<double, std::string>> KNN::distance(std::vector<double> a) {
    std::vector<std::tuple<double, std::string>> dis_from_point;
    double tmp;
    for (int i = 0; i < KNN::data.size(); ++i) {
        //add calcDistance to distance file
        tmp = calcDistance(distance_metric, a, data[i].getAll());
        dis_from_point.emplace_back(tmp, data[i].getType());
    }
    return dis_from_point;
}

/**
 * Receives an array of distances and finds the max label that appears.
 * @param distances Rhe vector obtained from the distance method.
 * @return The label that appears most in the distances vector
 */
std::string KNN::nearestNeighbor(std::vector<std::tuple<double, std::string>> distances) const {
    //sort distances based on first element in ascending order
    std::sort(distances.begin(), distances.end());
    std::vector<std::string> label_of_dis;
    std::string most_common;
    for (int i = 0; i < k; ++i) {
        label_of_dis.emplace_back(std::get<1>(distances[i]));
    }
    sort(label_of_dis.begin(), label_of_dis.end());
    std::string check = label_of_dis[0];
    std::string max_label = check;
    int count = 0;
    int max = 0;
    for (int i = 0; i < label_of_dis.size(); ++i) {
        if (check == label_of_dis[i]) {
            count++;
        } else {
            if (count > max) {
                max = count;
                max_label = check;
            }
            count = 0;
            check = label_of_dis[i];
        }

    }
    return max_label;
}
