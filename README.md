# AP_Task2

**This project was built by Daniel Lifshitz and Adira Weiss.**

**In this project we predict the classification of a given vector using the KNN algorithm and a file of classified vectors.**

## The Files:

### CalcDist.h/cpp:
Performs the calculation of all the distances from the vector to the points for the KNN algorithm.

### KNN.h/cpp:
Implementation of the KNN algorithm. 
Time complexity: O(n*log(n)),
Space complexity: O(n)
(n is the number of vectors).

### Point.h/cpp:
Merges both the vectors and their classification into a Point object and implements the getters and setters.

### PointReader.h/cpp:
Reads the given .csv file and creates all the classified points.

### SafetyChecks.h/cpp:
With those files we implement all the edge cases tests and checking for wrong input.

### ex2.cpp:
Runs the entire program and prints the inputted vectors predicted classification.

**Run and compile**

If the only files you have in your directory are the needed files, mainly ```ex2.cpp```, ```CalcDist.cpp```, ```KNN.cpp```, ```Point.cpp```, ```PointReader.cpp``` and ```SafetyChecks.cpp``` **and their headers (.hpp)**.

You can compile the code with this command:  
```
g++ -std=c++11 *.cpp -o
```
Otherwise, you need to list them:
```
g++ -std=c++11  ex2.cpp CalcDist.cpp KNN.cpp Point.cpp PointReader.cpp SafetyChecks.cpp
```

You can also use the attached Makefile with the following command:
```
make
```

To run on linux/mac: 
```
./a.out k file distancemetric
```
To run on Windows:
```
a.out k file distancemetric
```
**If the file isn't given with the proper path, it must be in your working directory.**
<br>**The argument in the run command consists of 3 parts:**
* K - number of neighbors to check.
  * K must be a number bigger than zero and smaller than the number of vectors in the .csv file.
  * If K is a float it will be rounded down.
* The name of the file with the classified vectors.
    * The file must be a .csv file.
* A distance metric:
    * AUC
    * MAN
    * CHB
    * CAN
    * MIN

**Example**
````
./a.out 3 iris_classified.csv MAN
````
**For any Invalid input in the run command, the program will print an error message and exit the program.**<br>

**Input Instructions**
* The input vector must be a list of numbers separated by spaces. The size of the input vector must be the same as the size of the vectors in the .csv file.
* All vectors in the .csv file must be the same size.

**Example**
If you input:
```
1 2 3 4
```
You will get:
```
Iris-versicolor
```
**For invalid input of the unclassified vector, the program will print an error message and ask you to input a new vector.**
