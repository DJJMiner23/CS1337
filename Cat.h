//Dayne John - CS1337.003
//Cat.h

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
//      changed the speak function to ostream as a parameter

#ifndef CAT_H
#define CAT_H

#include "Animal.h"

class Cat:public Animal {
  private:
    static int numberOfCats; //total count of the dogs
    int myCatNumber;  //unique number of the dog
  public:
    //GETTER
    static int getNumberOfCats();
    int getCatNumber() const;

    void speak(ostream &); //define the cat speak function to the output stream
    Cat();
};


#endif // CAT_H
