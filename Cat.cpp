//Dayne John - CS1337.003
//Cat.cpp

//changelog:
//  04/28/2021 - Dayne
//      created static count of cats variable
//      set this file up to inherit everything including the attributes from the Animal class header file
//      created myCatNumber which is the unique number for the cat
//  04/29/2021 - Dayne
//      created my getter for myCatNumber for the Cat class
//  04/30/2021 - Dayne
//      created the speak function and set it to the of stream
//  05/01/2021 - Dayne
//      set ostream as a Cat::speak parameter

#include "Cat.h"

using namespace std;

//Cat::speak
void Cat::speak(ostream &o) {
    o <<  "\n" << sound << endl;
    o << "Hi my name is " << name << "! " << endl;
    o << "I am a " << type << "." << endl;
    o << "My breed is " << breed << "." << endl;
    o << "My age is " << age << "." << endl;
    o << "My weight is " << weight << " lbs." << endl;
    o << "My Cat Number is " << myCatNumber << " and my Animal Number is " << myAnimalNumber << "." << endl;
    o << "My color is " << color << "." << endl;
    o << "My health status is: " << health << endl << endl; // for the extra line at the end
} //Cat::speak

//Cat::Cat
Cat::Cat() {
    type = "";
    name = "";
    age = "";
    weight = "";
    breed = "";
    color = "";
    health = "";
    numberOfCats++;
    myCatNumber = numberOfCats;
} //Cat::Cat

int Cat::numberOfCats; //make sure we are in the scope of cat

//GETTERS
int Cat::getNumberOfCats() {
    return numberOfCats;
}

int Cat::getCatNumber() const {
    return myCatNumber;
}
