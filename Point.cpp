//
// Created by Daniel Lifshitz on 30/11/2022.
//

#include "Point.h"
/**
 * @brief Iris will be represented as points in space as it is the same and could be minimally changed to fit other descriptions.
 */


/**
 * @brief Construct a new Point:: Point object using a vector and a type
 *
 * @param Cords A vector of information about the point.
 * @param type The type of the point.
 */
Point::Point(std::vector<double> Cords, std::string type)
        : pointCords(Cords), type(type) {}

/**
 * @brief Construct a new Point:: Point object using a different point.
 *
 * @param point The point we copy.
 */
Point::Point(const Point& point){
    for (int i = 0; i < point.getAll().size(); i++){
        this->pointCords.push_back(point.getCord(i));
    }
    this->type = point.getType();
}



/**
 * @brief Specific getter.
 * Will return a specific coordinate in the point.
 * for example: in (x,y,z) you could get x y or z.
 *
 * @return double The coordinate of the point asked by the user.
 */
double Point::getCord(int place) const {
    if(place >=0 && place <= pointCords.size()){
        return pointCords[place];
    }
    else {
        std::cout << "No coordinate like that exists please pick another number";
        return 0;
    }
}

/**
 * @brief Type getter.
 *
 * @return pointType The type the point has.
 */
std::string Point::getType() const{
    return type;
}

/**
 * @brief Point getter.
 * Will return the entire point.
 * for example: with (x,y,z) you will get (x,y,z).
 *
 * @return std::vector<double> The entire point.
 */
std::vector<double> Point::getAll() const {
    return pointCords;
}


/**
 * Setting a point using a string.
 * @param v The string of the point. (for example: 1 2 3 4 5 pointType)
 * @param spacer The space between coordinates in the string. (for example: ' ')
 */
void Point::setFromString(std::string v, char spacer) {
    bool validInput = true;
    std::vector<double> v2;
    //using code from Task 1.
    std::stringstream ss(v);
    std::string s;
    while (std::getline(ss, s, spacer)) {
        if (IsDouble(s)) {
            v2.push_back(stod(s));
        }
        else {
            //This is the type.
            validInput = false;
            std::cout << "Invalid input." << std::endl;
            break;
        }
    }
    if (validInput) {
        this->pointCords = v2;
    }
}

/**
 * Setting a point using a vector of string (for example: {"1","2","3","4","5","pointType"})
 * @param Cords The coordinates of the point we want to set.
 */
void Point::setFromVector(std::vector<std::string> Cords) {
    this->pointCords.clear();
    for (int i = 0; i < Cords.size() - 1; i++){

        if (IsDouble(Cords[i])){
            this->pointCords.push_back(std::stod(Cords[i]));
        }
        else {
            //By clearing the pointCords we invoke the error that not all the vectors are the same size.
            this->pointCords.clear();
            break;
        }
    }
    this->type = Cords[Cords.size()-1];
}

/**
 * << operator for Point.
 * @param os The out stream
 * @param point Point object
 * @return Out stream.
 */
std::ostream &operator<<(std::ostream &os, const Point &point) {
    std::string output = "";
    for (int i = 0; i < point.getAll().size(); i++){
        output += std::to_string(point.getCord(i));
        output += " ";
    }
    output += point.getType();
    return os << output;
}

/**
 * Checking if maybeDouble is a number.
 * @param maybeDouble The string we got we want to confirm to a number.
 * @return True if the first digit is a number; false otherwise.
 */
bool IsDouble(std::string maybeDouble){
    int firstDigit = maybeDouble[0] - '0';
    if (firstDigit >= 0 && firstDigit <= 9){
        //The function stod(maybeDouble) will return a double even if there are letters in th number.
        return true;
    }
    //The first digit is not a number thus stod(maybeDouble) will return an error and we do not want that to happen.
    return false;
}

