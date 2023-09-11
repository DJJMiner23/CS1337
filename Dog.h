//Dayne John - CS1337.003
//Dog.h

//changelog:
//  04/28/2021 - Dayne
//      created static count of dogs variable
//      set this file up to inherit everything including the attributes from the Animal class header file
//      created myDogNumber which is the unique number for the dog
//  04/29/2021 - Dayne
//      created my getter for myDogNumber for the Dog class
//  04/30/2021 - Dayne
//      created the speak function and set it to the of stream
//  05/01/2021 - Dayne
//      changed the speak function to ostream as a parameter

#ifndef DOG_H
#define DOG_H

#include "Animal.h"

class Dog:public Animal {
  private:
    static int numberOfDogs; //total count of the dogs
    int myDogNumber; //unique number of the dog

  public:
    //GETTER
    static int getNumberOfDogs();
    int getMyDogNumber() const;

    void speak(ostream &); //define the dog speak function to the output stream
    Dog();
};



#endif // DOG_H
