//Dayne John - CS1337.003
//Animal Shelter

//  changelog:
//  04/28/2021 - Dayne
//      created the program
//      created all the variable and vectors necessary for the cat, dog, and animal classes
//      created a function to read the file
//  04/29/2021 - Dayne
//      created a function to parse the file
//      created a function to change the entire string to lowercase
//  04/30/2021 - Dayne
//      created a function to identify the animal and to create an animal object
//      created multiple functions to store each animal in their respective vectors (cats, dogs, animals, other animals)
//  04/31/2021 - Dayne
//      created multiple functions to write all 4 reports to the output file
//      reorganized the functions and gave more self-explanatory names to the functions
//      added more comments to clarify each function's purpose
//      improved the spacing of the program
//      made the program more user-friendly
//  05/01/2021 - Dayne
//      changed my program to print the output to an output file and the console

//  notes:
//      This program creates an Animal Shelter, and then it reads data from a csv file and stores information about each animal into the shelter.
//      Once the information of each animal is gathered, it writes reports on the animals regarding their age, the total number of animals, adoptable animals, etc.
//      to an output file called "Dayne's Animal Shelter Report.txt"

#include <iostream> //for input and output
#include <string> //for manipulating each string
#include <vector> //for cats, dogs, and animals vector
#include <fstream> //for file reading
#include "Animal.h"
#include "Cat.h"
#include "Dog.h"

using namespace std;

//VECTORS
vector<Cat> cats;
vector<Dog> dogs;
vector<Animal> allAnimals;
vector<Animal> otherAnimals;
//******************************

/*void show(vector <string> v) {
for(string i: v) {
    cout << i;
}

}
FOR DEBUGGING
*/

//ParseTheFile
vector<string> ParseTheFile(string line) {
    vector<string> values; //create a vector of the values in the file
    line = line + ",";
    string temp = "";
    for(char x: line) {
        if(x == ',') { //look for commas
            values.push_back(temp); //and push it into the vector
            temp = "";
        } else {
            temp = temp+x; //adding current letter from the line to the temporary string
        }
    }
//show(values); FOR DEBUGGING
    return values;
} //ParseTheFile

//lowerwholestring
void lowerwholestring(string &s) {
    for(char &c: s)
        c = tolower(c);
} //lowerwholestring

/*
 void DisplayValueAtIndex(Animal a, int i) {
                cout << "Value @ " << i << " is " << a.getType() << endl;
} FOR DEBUGGING
*/


//storeCatInCatVector
void storeCatInCatVector(vector<string> v) {
    Cat newCat; //create cat object
    newCat.setType(v.at(0)); //set each attribute for each cat
    newCat.setName(v.at(1));
    newCat.setAge(v.at(2));
    newCat.setWeight(v.at(3));
    newCat.setBreed(v.at(4));
    newCat.setColor(v.at(5));
    newCat.setHealth(v.at(6));
    newCat.setSound(v.at(7));
    cats.push_back(newCat); //push the new cat into the cats vector

    /* << "storeCatInCatVector";
    for (int i = 0; i < cats.size(); i++) {
    DisplayValueAtIndex(cats.at(i), i); FOR DEBUGGING
          } */

    allAnimals.push_back(cats.at(cats.size()-1));
} //storeCatinCatVector

//storeDoginDogVector
void storeDoginDogVector(vector<string> v) {
    Dog newDog; //create dog object
    newDog.setType(v.at(0)); //set each attribute for each dog
    newDog.setName(v.at(1));
    newDog.setAge(v.at(2));
    newDog.setWeight(v.at(3));
    newDog.setBreed(v.at(4));
    newDog.setColor(v.at(5));
    newDog.setHealth(v.at(6));
    newDog.setSound(v.at(7));
    dogs.push_back(newDog);
    allAnimals.push_back(dogs.at(dogs.size()-1));

    /*for (int i = 0; i < dogs.size(); i++) {
        DisplayValueAtIndex(dogs.at(i), i);
                 } FOR DEBUGGING
        */
} //storeDoginDogVector


//storeOtherAnimalsInOtherAnimalsVector
void storeOtherAnimalsInOtherAnimalsVector(vector<string> v) {
    Animal newAnimal; //create animal object
    newAnimal.setType(v.at(0)); //set each attribute for each animal
    newAnimal.setName(v.at(1));
    newAnimal.setAge(v.at(2));
    newAnimal.setWeight(v.at(3));
    newAnimal.setBreed(v.at(4));
    newAnimal.setColor(v.at(5));
    newAnimal.setHealth(v.at(6));
    newAnimal.setSound(v.at(7));
    otherAnimals.push_back(newAnimal);

    /*for (int i = 0; i < otherAnimals.size(); i++) {
    DisplayValueAtIndex(otherAnimals.at(i), i); FOR DEBUGGING
            }*/

    allAnimals.push_back(otherAnimals.at(otherAnimals.size()-1));
} //storeOtherAnimalsInOtherAnimalsVector

//IdentifyTheAnimalTypeAndMakeAnimal
void IdentifyTheAnimalTypeAndMakeAnimal(vector<string> v) {
    string AnimalType = v.at(0);
    //cout << AnimalType; FOR DEBUGGING
    lowerwholestring(AnimalType); //change the letters to lower case
    //cout << AnimalType; FOR DEBUGGING

    if(AnimalType == "cat") { //if the animal is a cat then store it in the Cat vector
        storeCatInCatVector(v);
    } else if(AnimalType == "dog") { //if the animal is a dog then store it in the Dog Vector
        storeDoginDogVector(v);
    } else {
        storeOtherAnimalsInOtherAnimalsVector(v); //store the other animals in the other animals vector
    }

} //IdentifyTheAnimalTypeAndMakeAnimal


//ReadTheFile
void ReadTheFile() {
    ifstream inputFile("Animal Shelter Data-05.csv"); //hardwired the file name
    if (!inputFile) { //if file doesn't open correctly, then display wrong file output
        cout << "Sorry, we couldn't find that file. Please check that the file is located in the correct directory and try again.";
        return;
    }
    string line; //used as a placeholder
    getline(inputFile, line); //read in line
    while(!inputFile.eof()) { //read the file while we are not at the end of the file
        getline(inputFile, line);
        if(line == "") { //if the line is empty then leave
            break;
        }
        //cout << "Line just read in = " << line << endl; FOR DEBUGGING
        vector<string> attributes = ParseTheFile(line);
        //show(attributes); FOR DEBUGGING
        IdentifyTheAnimalTypeAndMakeAnimal(attributes);
        /*if(attributes.at(0) == "") { FOR DEBUGGING
            break;
        } */
    }
    inputFile.close(); //close the file

} //ReadTheFile

//displayTotalAnimalReport
void displayTotalAnimalReport(ostream &output) {
//cout <<"Display Total Animal Report"; FOR DEBUGGING
    output << "Welcome to Dayne's Animal Shelter! Below this is a list of all the Animals that we have here at the shelter. " << endl; //user friendly message
    output << "\nReport 1 (All Animals): " << endl;
    output << "The total number of animals is = " << Animal::getNumberOfAnimals() << endl;
    output << "The total number of cats is = " << Cat::getNumberOfCats() << endl;
    output << "The total number of dogs is = " << Dog::getNumberOfDogs() << endl;
    output << "********************************" << endl;
} //displayTotalAnimalReport

//DisplayCatReport
void DisplayCatReport(ostream &output) {
//cout << "Cat Report";  FOR DEBUGGING
    output << "\nReport 2 (Cats): " << endl; //write report to output file
    for(Cat someCat: cats) {
        someCat.speak(output);
    }
    output << "********************************" << endl;
} //DisplayCatReport

//DisplayDogReport
void DisplayDogReport(ostream &output) {
//cout << "Dog Report"; FOR DEBUGGING
    output << "\nReport 3 (Dogs): " << endl; //write report to output file
    for(Dog someDog: dogs) {
        someDog.speak(output);
    }
    output << "********************************" << endl;
} //DisplayDogReport

//findAdoptableAnimals
vector<Animal> findAdoptableAnimals() {
    vector <Animal> adoptableAnimals; //create a vector for adoptable animals
    for(Animal someAnimal: allAnimals) { //loop through the vector of all animals
        if(someAnimal.getHealth().find("good")!= -1) { //if the animal has good health
            adoptableAnimals.push_back(someAnimal); //then add it to the adoptable animals
        }
    }
    return adoptableAnimals;

} //findAdoptableAnimals

//DisplayAdoptableAnimals
void DisplayAdoptableAnimals(ostream &output) {
//cout << "Adoptable Animal Report"; FOR DEBUGGING
    output << "Report 4 (Adoptable Animals): " << endl;
    vector <Animal> adoptMe = findAdoptableAnimals(); //find adoptable animals for the adoptable animal vectors
    for(Animal adoptableAnimal: adoptMe) {
        adoptableAnimal.speak(output);
        output << "I'm Adoptable. Pick me!" << endl;
    }
    output << "********************************" << endl;
    output << "\nThank you for visiting Dayne's Animal Shelter! Have a great day! " << endl; //user-friendly message

} //DisplayAdoptableAnimals

//main
int main() {
    ofstream outputFile("Dayne's Animal Shelter Report.txt"); //cresting an ofstream object ouput file set as Dayne's Animal Shelter Report.txt
    ReadTheFile();

    //write to output file
    displayTotalAnimalReport(outputFile);
    DisplayCatReport(outputFile);
    DisplayDogReport(outputFile);
    DisplayAdoptableAnimals(outputFile);

    //display to console
    displayTotalAnimalReport(cout);
    DisplayCatReport(cout);
    DisplayDogReport(cout);
    DisplayAdoptableAnimals(cout);
    outputFile.close(); //close the file

    return 0;
} //main


