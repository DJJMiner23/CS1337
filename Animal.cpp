//Dayne John - CS1337.003
//Animal.cpp

//changelog:
//  04/28/2021 - Dayne
//      defined the setters for each attribute of the animal
//      gave default values to each animal that didn't have a certain attribute
//      set this file up to inherit everything including the attributes from the Animal class header file
//  04/29/2021 - Dayne
//      created my getter for myCatNumber for the Cat class
//  04/30/2021 - Dayne
//      defined the speak function for Animal and set it to the of stream
//  05/01/2021 - Dayne
//      set ostream as a Animal::speak parameter

#include "Animal.h"

using namespace std;
//using namespace Animal;


//SETTERS
void Animal::setName(string n) {
    if(n=="") {
        name = "unknown ";
    } else {
        name = n;
    }
}

void Animal::setType(string t) {
    if(t=="") {
        type = "unknown ";
    } else {
        type = t;
    }
}


void Animal::setAge(string a) {
    if(a=="") {
        age = "unknown ";
    } else {
        age = a + " year(s) old";
    }
}

void Animal::setWeight(string w) {
    if(w=="") {
        weight = "unknown";
    } else {
        weight = w;
    }
}

void Animal::setBreed(string b) {
    if(b=="") {
        breed = "unknown";
    } else {
        breed = b;
    }

}

void Animal::setColor(string c) {
    if(c=="") {
        color = "unknown. ";
    } else {
        color = c;
    }
}

void Animal::setHealth(string h) {
    if(h=="") {
        health = "unknown. ";
    } else {
        health = h;
    }
}
void Animal::setSound(string s) {
    if(s=="") {
        sound = "Slight breathing noise. ";
    } else {
        sound = s;
    }
}

//Animal::speak
void Animal::speak(ostream &o) {
    o <<  "\n" << sound << endl;
    o << "Hi my name is " << name << "! " << endl;
    o << "I am a " << type << "." << endl;
    o << "My breed is " << breed << "." << endl;
    o << "My age is " << age << "." << endl;
    o << "My weight is " << weight << " lbs." << endl;
    o << "My Animal Number is " << myAnimalNumber << "." << endl;
    o << "My color is " << color << "." << endl;
    o << "My health status is: " << health << endl << endl; // for the extra line at the end
} //Animal::speak

//Animal::Animal
Animal::Animal() {
    type = "";
    name = "";
    age = "";
    weight = "";
    breed = "";
    color = "";
    health = "";
    numberOfAnimals++;
    myAnimalNumber = numberOfAnimals;
} //Animal::Animal


int Animal::numberOfAnimals; //make sure we are in the scope of Animal


//GETTERS

//numberOfAnimals
int Animal::getNumberOfAnimals() {
    return numberOfAnimals;
}

//myAnimalNumber
int Animal::getMyAnimalNumber() const {
    return myAnimalNumber;
}

//Type
string Animal::getType() const {
    return type;
}

//Age
string Animal::getAge() const {
    return age;
}

//Breed
string Animal::getBreed() const {
    return breed;
}

//Weight
string Animal::getWeight() const {
    return weight;
}

//Color
string Animal::getColor() const {
    return color;
}

//Health
string Animal::getHealth() const {
    return health;
}

//Sound
string Animal::getSound() const {
    return sound;
}
