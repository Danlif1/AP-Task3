//
// Created by Daniel Lifshitz on 30/11/2022.
//

#include "SafetyChecks.h"

/**
 * @brief checks that there is a K, file and a distance.
 *
 * @param argc the amount of things given.
 * @return true The amount is ok.
 * @return false The amount is not ok.
 */
bool NumberOfArguments(int argc){
    if (argc == 4){
        return true;
    }
    else if (argc < 4){
        std::cout << "Insufficient information please enter more arguments in the command line" << std::endl;
    }
    else {
        std::cout << "Too much information please enter less arguments in the command line" << std::endl;
    }
    return false;

}

/**
 * @brief Checks the amount of points given and the amount of points needed for the KNN algorithm is ok.
 *
 * @param k The amount of points of points needed for the KNN algorithm.
 * @param amountOfPoints The amount of points given.
 * @return true The K is ok.
 * @return false The K is not ok.
 */
bool PointsCount(long k, long amountOfPoints){
    if (k > 0 && k < amountOfPoints){
        return true;
    }
    else if (k <= 0){
        std::cout << "K is too small, please enter a bigger number as K" << std::endl;
    }
    else{
        std::cout << "K is too big, please enter a smaller number as K" << std::endl;
    }
    return false;
}

/**
 * @brief stoi() doesn't work for numbers starting with a letter so we check if the first digit is a number.
 * We check the if because k[0] - '0' is actually the first digit of k and by that we can know if the first digit is a number or not.
 *
 * @param k The string given from argv for the KNN algorithm.
 * @return int return the actual number of k.
 */
bool KCheck(std::string k){
    int firstDigit = k[0]-'0';
    if (firstDigit >= 0 && firstDigit < 10){
        return true;
    }
    std::cout << "K should be a number" << std::endl;
    return false;
}

/**
 * Checking if all the points in the array points have the same amount of coordinates.
 * @param points The array of points we check on.
 * @return False if not all the points has the same amount of coordinates; True otherwise.
 */
bool IsSameSize(std::vector<Point> points){
    int goodSize = points[0].getAll().size();
    for(int i = 0; i < points.size(); i++){
        if (goodSize != points[i].getAll().size()){
            return false;
        }
    }
    return true;
}

/**
 * Checking if both points have vectors that are the same size.
 * @param uPoint The first point.
 * @param cPoint The second point.
 * @return True if both vectors are the same size; false otherwise.
 */
bool GoodVector(Point uPoint, Point cPoint){
    if(uPoint.getAll().size() == cPoint.getAll().size()){
        return true;
    }
    return false;
}

/**
 * Checking that the file name ends with .csv
 * @param fileName The name of the file.
 * @return True if the file ends with .csv; false otherwise.
 */
bool CheckFile (std::string const &fileName) {
    //Helped by https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c.
    std::string fileEnding = ".csv";
    if (fileName[fileName.size()-4] == '.') {
        if (fileName[fileName.size()-3] == 'c') {
            if (fileName[fileName.size()-2] == 's') {
                if (fileName[fileName.size() - 1] == 'v') {
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Checking if the distance metric is one of the given five.
 * @param metric The distance metric we got.
 * @return True if the metric is one of the given five; false otherwise.
 */
bool CheckMetric(std::string metric){
    for (int i = 0; i < 3; i++) {
        metric[i] = std::toupper(metric[i]);
    }
    int isEqual = metric.compare("AUC");
    if (!isEqual) {
        //Meaning its AUC.
        return true;
    }
    isEqual = metric.compare("MAN");
    if (!isEqual) {
        //Meaning its MAN.
        return true;
    }
    isEqual =  metric.compare("CHB");
    if (!isEqual) {
        //Meaning its CHB.
        return true;
    }
    isEqual = metric.compare("CAN");
    if (!isEqual) {
        //Meaning its CAN.
        return true;
    }
    isEqual = metric.compare("MIN");
    if (!isEqual) {
        //Meaning its MIN.
        return true;
    }
    std::cout << "Invalid metric name." << std::endl;
    return false;
}