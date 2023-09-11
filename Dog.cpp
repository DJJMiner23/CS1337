//Dayne John - CS1337.003
//Dog.cpp

//changelog:
//  04/28/2021 - Dayne
//      created static count of dogs variable
//      set this file up to inherit everything including the attributes from the Animal class header file
//      created myDogNumber which is the unique number for the dog
//  04/29/2021 - Dayne
//      created my getter for myCatNumber for the Dog class
//  04/30/2021 - Dayne
//      created the speak function and set it to the of stream
//  05/01/2021 - Dayne
//      set ostream as a Dog::speak parameter

#include "Dog.h"

using namespace std;

//Dog::speak
void Dog::speak(ostream &o) {
  o <<  "\n" << sound << endl;
  o << "Hi my name is " << name << "! " << endl;
  o << "I am a " << type << "." << endl;
  o << "My breed is " << breed << "." << endl;
  o << "My age is " << age << "." << endl;
  o << "My weight is " << weight << " lbs." << endl;
  o << "My Dog Number is " << myDogNumber << " and my Animal Number is " << myAnimalNumber << "." << endl;
  o << "My color is " << color << "." << endl;
  o << "My health status is: " << health << endl << endl; // for the extra line at the end
} //Dog::speak

//Dog::Dog
Dog::Dog() {
type = "";
name = "";
age = "";
weight = "";
breed = "";
color = "";
health = "";
numberOfDogs++;
myDogNumber = numberOfDogs;
} //Dog::Dog

int Dog::numberOfDogs; //make sure we are in the scope of dog

//GETTERS
int Dog::getNumberOfDogs() {
return numberOfDogs;
}

int Dog::getMyDogNumber() const{
    return myDogNumber;
}
