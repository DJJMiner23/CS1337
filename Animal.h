//Dayne John - CS1337.003
//Animal.h

//changelog:
//  04/28/2021 - Dayne
//      created static count of animals variable
//      created myAnimalNumber and all other attributes for the Animal class
//  04/29/2021 - Dayne
//      created my setters and getters for the Animal class
//  05/01/2021 - Dayne
//      changed the speak function to ostream as a parameter

#ifndef ANIMAL_H
#define ANIMAL_H

#include <string> //for manipulating each string
#include <iostream> //for input and output
#include <fstream> //for file reading

using namespace std;

class Animal {
  private:
    static int numberOfAnimals; //total count of all animals
  protected:
    int myAnimalNumber; //unique number for each animal
    string type; //type of animal
    string name; //name of the animal
    string age;  //age of the animal
    string weight; //weight of the animal
    string breed; //the breed of the animal
    string color; //the color of the animal
    string health; //the health of the animal
    string sound; //the sound that the animal makes

  public:
    //SETTERS
    void setType(string);
    void setName(string);
    void setAge(string);
    void setWeight(string);
    void setBreed(string);
    void setColor(string);
    void setHealth(string);
    void setSound(string);
    void speak(ostream &);  //set ostream as a parameter of speak

    //GETTERS
    string getType() const;
    string getAge()  const;
    string getName() const;
    string getWeight()const;
    string getColor() const;
    string getHealth()const;
    string getBreed() const;
    string getSound() const;
    static int getNumberOfAnimals();
    int getMyAnimalNumber() const;
    int getMyCatNumber() const;

    Animal();
};


#endif // ANIMAL_H
