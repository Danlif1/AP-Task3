
#include "SafetyChecks.h"
#include "Point.h"
#include "PointReader.h"
#include "KNN.h"

/**
 * The main function of the second task.
 * @param argc The amount of arguments gotten from the command line.
 * @param argv Supposed to have ./a.out k file distance_metric.
 */
int main(int argc, char **argv) {


    std::fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open("classified.csv", std::ios::out | std::ios::app);
    if(NumberOfArguments(argc)) {
        //Saving the K.
        int k;
        if (KCheck(argv[1])) {
            k = std::stoi(argv[1]);
        } else {
            //K is equal 0, so we need to terminate the program.
            std::cout << "K is not a valid number" << std::endl;
            return 0;
        }
        //Saving the file name.
        std::string file = argv[2];
        if (!CheckFile(file)) {
            //The file doesn't end with .csv so we need to terminate the program.
            std::cout << "The file doesn't end with .csv" << std::endl;
            return 0;
        }
        //Saving the distance metric.
        std::string metric = argv[3];
        if (!CheckMetric(metric)) {
            //The metric isn't one of the given 5 so we need to terminate the program.
            std::cout << "Incorrect metric type" << std::endl;
            return 0;
        }
        //Create classified vector.

        PointReader classifiedPointReader(file);
        Point cPoint;
        std::vector<Point> classifiedPoints;
        //creating an array of classified points.
        while (classifiedPointReader.getNextPoint(cPoint)) { classifiedPoints.push_back(cPoint); }
        if (!PointsCount(k, classifiedPoints.size())){
            //K is either too big or too small so we need to terminate the program.
            return 0;
        }
        if(!IsSameSize(classifiedPoints)){
            std::cout << "Not all vectors are valid, please use a different file." << std::endl;
            return 0;
        }
        //initializing a run of KNN
        KNN knn_run(k,metric);
        knn_run.fit(classifiedPoints);
        //Making an infinite loop to read points.
        while (true) {
            //sPoint = string point.
            Point uPoint;
            do {
                std::string sPoint;
                getline(std::cin, sPoint);
                //uPoint = unclassified point.
                uPoint.setFromString(sPoint, ' ');
                if (!GoodVector(uPoint, classifiedPoints[0])){
                    if (!uPoint.getAll().empty()) {
                        std::cout << "Please enter the correct number of arguments into the vector." << std::endl;
                    }
                } else {
                    std::cout << knn_run.predict(uPoint) << std::endl;
                }
            } while (!GoodVector(uPoint, classifiedPoints[0]));

        }
    }
    else {
        std::cout << "Insufficient arguments. Please enter a K, file and distance metric." << std::endl;
    }


}

