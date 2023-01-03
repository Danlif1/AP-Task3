# AP_Task3

**This project was built by Daniel Lifshitz and Adira Weiss.**

**In this project we implemented a server and a client to run the KNN algorithm from the previous assignment.<br>
The client will receive a vector from the user, send it to the server who will run the algorithm and send a prediction which then wil bee printed by the client*

## New Files:

### ServerMain.cpp:

### Server.h/cpp:

### ClientMain.cpp:

### Client.h/cpp:

### ClientInputChecks.cpp:


## Other Files:

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

If the only files you have in your directory are the files listed above,

You can compile the code with this command:  
```
g++ -std=c++11 *.cpp -o
```
Otherwise, you need to list them:
```
g++ -std=c++11  ex2.cpp CalcDist.cpp KNN.cpp Point.cpp PointReader.cpp SafetyChecks.cpp
```

You can compile the code using attached Makefile with the following command:
```
make
```
For the server:<br>
To run on linux:  
```
./server.out file.csv port
```
To run on Windows:
```
server.out file.csv port
```
**If the file isn't given with the proper path, it must be in your working directory.**

For the client:<br>
To run on linux:
```
./client.out ip port
```
To run on Windows:
```
client.out ip port
```
<br>**Arguments in run command:**
* file
  * must be a .csv file
* ip
    * must be a valid ip address.
* port
    * must be a valid port number (0-65535).

**Example Server**
````
./server.out iris_classified.csv 5555
````

**Example Client**
````
./client.out 127.0.0.1 5555
````

**For any Invalid input in the run command, the program will print an error message and exit the program.**<br>

**Input Instructions for Client:**
* The program will receive the following input from the user:
````
vector distance k
````
* The input vector must be a list of numbers separated by spaces. The size of the input vector must be the same as the size of the vectors in the .csv file.
* All vectors in the .csv file must be the same size.
* A distance metric:
  * AUC
  * MAN
  * CHB
  * CAN
  * MIN
* K - number of neighbors to check.
  * K must be a number bigger than zero and smaller than the number of vectors in the .csv file.
  * Must be an integer.

**Example**
If you input:
```
1 2 3 4 MAN 5
```
You will get:
```
Iris-versicolor
```
**For invalid input of any kind, the program will print an error message and ask you to input a new vector.**
