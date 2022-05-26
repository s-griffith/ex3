#ifndef EX3_HEALTHPOINTS_H
#define EX3_HEALTHPOINTS_H

#include <iostream>




/*
 *  HealthPoints:
 *  This class represents the health points object belonging to a player in the game
*/
class HealthPoints {
public:

    //Constant value for the default maximum health points a player can receive
    static const int DEFAULT_HP = 100;

    /*
     * C'tor of HealthPoints class
     *
     * @param hpoints - The maximum of health points for the player
     * @return
     *      A new instance of HealthPoints.
     */
    HealthPoints(int hpoints = DEFAULT_HP);

    /*
     * Explicitly use the default methods for the copy constructor, destructor the assignment operator
    */
    HealthPoints(const HealthPoints&) = default;
    HealthPoints& operator=(const HealthPoints& other) = default;
    ~HealthPoints() = default;

    //-----------------------------------Member Functions-------------------------------------


    /*
    * "+=" operator (hp1 += 50)
    *
    * @param addition - The integer value that needs to be added to the current health points
    * @return
    *      A reference to the current health point object
    */
    HealthPoints& operator+=(int addition);

    /*
    * "-=" operator (hp1 -= 50)
    *
    * @param subtraction - The integer value that needs to be subtracted to the current health points
    * @return
    *      A reference to the current health point object
    */
    HealthPoints& operator-=(int subtraction);

    /*
    * "+" operator with HP object first (hp1 = hp1 + 50)
    *
    * @param addition - The integer value that needs to be added to the current health points
    * @return
    *      A copy of the new health point object
    */
    HealthPoints operator+(int addition) const;

    /*
    * "-" operator with HP object first (hp1 = hp1 - 50)
    *
    * @param subtraction - The integer value that needs to be subtracted to the current health points
    * @return
    *      A copy of the new health point object
    */
    HealthPoints operator-(int subtraction) const;

    //------------------------------Friend Non-Member Functions-------------------------------

    /*
    * "==" operator (comparison = (hp1 == hp2);   comparison = (100 == hp1);   comparison = (hp1 == 100))
    *
    * @param hp1 - The first health point object
    * @param hp2 - The second health point object
    * @return
    *      true if the current health points of both objects are equal, otherwise false.
    */
    friend bool operator==(const HealthPoints& hp1, const HealthPoints& hp2);

    /*
    * "<" operator between two HP objects (comparison = (hp1 < hp2))
    *
    * @param hp1 - The first health point object
    * @param hp2 - The second health point object
    * @return
    *      true if the current health points of the first object is smaller than the second, otherwise false.
    */
    friend bool operator<(const HealthPoints& hp1, const HealthPoints& hp2);

    /*
    * Output stream operator in the format: "<currentHealthPoints>(<maximumHealthPoints>)"
    *
    * @param os - The os stream
    * @param hp1 - The health point object to print
    * @return
    *      a reference to the os stream
    */
    friend std::ostream& operator<<(std::ostream& os, const HealthPoints& hp1);

    //Include the class if invalid arguments were entered to the constructor
    class InvalidArgument;

private:
    //Current number of health points and the maximum number possible
    int m_hp;
    int m_maxHP;
};

//---------------------------Non-Friend Non-Member Functions-----------------------------

/*
* "+" operator with HP object second (hp1 = 50 + hp1)
*
* @param addition - The integer value that needs to be added
* @param hp1 - the health point object that the "addition" needs to be added to
* @return
*      A copy of the new health point object
*/
HealthPoints operator+(int addition, const HealthPoints& hp1);

/*
* "-" operator with HP object second (hp1 = 50 - hp1)
*
* @param subtraction - The integer value that needs to be subtracted
* @param hp1 - the health point object that the "subtraction" needs to be subtracted from
* @return
*      A copy of the new health point object
*/
HealthPoints operator-(int subtraction, const HealthPoints& hp1);

/*
* "!=" operator (comparison = (hp1 != hp2);   comparison = (100 != hp1);   comparison = (hp1 != 100))
*
* @param hp1 - The first health point object
* @param hp2 - The second health point object
* @return
*      true if the current health points of both objects are not equal, otherwise false.
*/
bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2);

/*
* "<=" operator between two HP objects (comparison = (hp1 <= hp2))
*
* @param hp1 - The first health point object
* @param hp2 - The second health point object
* @return
*      true if the current health points of the first object is smaller than or equal to the second, otherwise false.
*/
bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2);

/*
* ">" operator between two HP objects (comparison = (hp1 > hp2))
*
* @param hp1 - The first health point object
* @param hp2 - The second health point object
* @return
*      true if the current health points of the first object is bigger than the second, otherwise false.
*/
bool operator>(const HealthPoints& hp1, const HealthPoints& hp2);

/*
* ">=" operator between two HP objects (comparison = (hp1 >= hp2))
*
* @param hp1 - The first health point object
* @param hp2 - The second health point object
* @return
*      true if the current health points of the first object is bigger than or equal to the second, otherwise false.
*/
bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2);


//--------------------------------Class Invalid Argument---------------------------------

/*
 *  HealthPoints::InvalidArgument
 *  This class is used for the errors thrown as a result of invalid arguments
*/
class HealthPoints::InvalidArgument {
public:

    /*
     * C'tor of InvalidArgument class
     *
     * @param argument - The invalid argument received by the HealthPoints constructor
     * @return
     *      A new instance of InvalidArgument.
     */
    InvalidArgument(int argument) : m_invalidArgument(argument) {}
private:
    int m_invalidArgument;
};

#endif //EX3_HEALTHPOINTS_H