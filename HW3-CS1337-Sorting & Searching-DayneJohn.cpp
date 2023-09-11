//Dayne John - CS1337.003
//Sorting & Searching

//changelog:
//  03/05/2021 - Dayne
//      set up the program to read and validate user input
//      created a function to generate random numbers and vectors to store the random numbers
//  03/08/2021 - Dayne
//      created the function to sort the random numbers using STL
//  03/09/2021 - Dayne
//      created the Bubble Sort function to sort the random numbers
//  03/11/2021 - Dayne
//      created the Binary Search function to search for the number that the user inputs
//      created the function that removes the duplicates from the random numbers
//  03/12/2021 - Dayne
//      found a bug where only some duplicates were being removed
//      fixed the bug and realized it was an off by one error
//  03/13/2021 - Dayne
//      improved spacing of the program
//      reorganized the order of the functions
//      improved variable and function names to be more self-documenting
//      made the program more user-friendly

//  notes:
//  This program generates random numbers based on user input into a vector and then sorts them using STL and the Bubble Sort algorithm.
//  It then copies the numbers into a new vector.
//  Then the program implements the Binary Search algorithm to find a number inputted by the user.
//  This program makes sure that the numbers you enter are valid.

#include <iostream> ////for input and output
#include <vector>  //for .push_back, size, capacity
#include <algorithm> //for sort() and erase() function
#include <conio.h> ////for console input and output
#include <ctime> //for random numbers

using namespace std;

int maxValueOfNum; //highest number that can be generated out of the random numbers
int randomNumber; //the random number that is generated
int num; //number for user to search for
int maxRandomNums; //the number of random numbers the user wants to generate
bool validNum = true;
vector<int> randomNumbers; //vector to store the random numbers
vector<int> copyOfRandomNumbers; //copy of the original vector
bool showflowControl = false; //debugging switch to make the program talk to me
//***********************************************//

//showflow
void showflow(string msg) {
    if (showflowControl) {
        cout << "--- at: " << msg << endl;
    }
} //showflow

//getUserInput
void getUserInput() {
    showflow("UserInput");
    cout << "Welcome to the Sort and Search Program!\n\nHow many numbers would you like to generate?" << endl; //ask user how many numbers they want to generate
    cin >> maxRandomNums;
    while(maxRandomNums <= 0) {
        cout << "Sorry that is an invalid number. Please enter a valid number. " << endl; //make sure number isn't negative
        cin >> maxRandomNums;
    }
    cout << "How large do you want the random numbers to be? The random numbers can be no greater than than 20." << endl; //ask for highest number that the user wants to generate
    cin >> maxValueOfNum;

    if(maxValueOfNum > 20 || maxValueOfNum < 1) { //if the highest number is greater than 20 or less than 1
        validNum = false;
    }

    while(!validNum) { //keep prompting the user until they enter a valid number
        cout << "Sorry that is an invalid number. Please enter a valid number that is not greater than 20." << endl;
        cin >> maxValueOfNum;
        if(maxValueOfNum <= 20 && maxValueOfNum > 0) { //validate user input
            validNum = true;
        }
    }
    showflow("Leaving UserInput.");
} //getUserInput

//displayVector
void displayVector(vector<int> vec) {
    showflow("Displaying Vector");
    for(int x: vec) {
        cout << x << "|"; //show the random numbers
    }
    cout << "\nVector Size: " << vec.size() << endl; //display size
    cout << "Capacity: " << vec.capacity() << endl; //display capacity
    showflow("Vector Displayed");
} //displayVector

//generateRandomNumbers
void generateRandomNumbers() {
    showflow("Random Numbers");
    if(validNum) { //if they are valid numbers within range
        srand(time(0));
    }
    for(int i = 0; i < maxRandomNums; i++) { //then generate as many random numbers that the user asked to generate
        randomNumber = (rand() % maxValueOfNum) + 1;
        randomNumbers.push_back(randomNumber); //make space for each new random number
    }
    cout << "\n\nUnsorted, Vector 1:" << endl;
    displayVector(randomNumbers); //show the random numbers
    showflow("Exiting Random Numbers");
} //generateRandomNumbers

//sortTheRandomNumbers
void sortTheRandomNumbers() {
    showflow("Random Numbers sorted");
    copyOfRandomNumbers = randomNumbers; //copy the contents of the first vector (randomNumbers) into the second vector (copyOfRandomNumbers)
    sort(randomNumbers.begin(), randomNumbers.end()); //sort the random numbers using the stl function
    cout << "\n\nSorted, Vector 1:" << endl;
    displayVector(randomNumbers); //show the random numbers
    showflow("The Random Numbers have been sorted");
} //sortTheRandomNumbers

//bubbleSort
void bubbleSort() {
    showflow("Bubble Sorting the Random Numbers");
    for(int i = 0; i < copyOfRandomNumbers.size()-1; i++) {
        for(int j = 0; j < copyOfRandomNumbers.size() - i - 1; j++) {
            if(copyOfRandomNumbers[j] > copyOfRandomNumbers[j+1]) {
                int value = copyOfRandomNumbers[j]; //hold the greater value
                copyOfRandomNumbers[j] = copyOfRandomNumbers[j+1]; //move the lowest value to the left
                copyOfRandomNumbers[j+1] = value; //move the greater value to the right
            }
        }
    }
    cout << "\n\nVector 2, sorted using Bubble Sort: ";
    cout << endl;
    displayVector(copyOfRandomNumbers);
    showflow("The Random Numbers have been Bubble Sorted.");
} //bubbleSort

//binarySearch
void binarySearch() {
    showflow("Binary Search in progress");
    cout << "\n\nEnter a number to search for: " << endl;
    cin >> num;
    int lowerElement = 0;
    int higherElement = randomNumbers.size()-1;
    int middleElement = 0;
    int totalDuplicateNums = 0; //counter to keep track of duplicate numbers
    bool wereTheNumbersFound = false;

    while(lowerElement < higherElement) {
        middleElement = (lowerElement + higherElement) / 2;
        if(randomNumbers.at(middleElement) == num) { //if the middle element is equal to the number that the user entered, then leave.
            wereTheNumbersFound = true;
            break;
        } else if(num < randomNumbers.at(middleElement)) { //if the number is less than the middle element
            higherElement = middleElement-1; //number is in lower half
        } else if(num > randomNumbers.at(middleElement)) { //if the number is greater than the middle element
            lowerElement = middleElement+1; //number is in upper half
        }
    }
    if(!wereTheNumbersFound) { //if numbers wasn't found
        cout << "The number " << num << " wasn't found" << " in Vector 1." << endl; //then number doesn't exist in vector so report
        return;
    }
    for(int i = middleElement; i < randomNumbers.size(); i++) { //go through the upper half starting from the middle element
        if(randomNumbers.at(i) == num) { //if a number is found multiple times in the upper half
            totalDuplicateNums++; //add to the count of duplicates
        }
    }
    for(int j = middleElement - 1; j >= 0; j--) { //go through the lower half starting from the middle bound
        if(randomNumbers.at(j) == num) { //if a number is found multiple times in the lower half
            totalDuplicateNums++; //add to the count of duplicates
        }
    }
    cout << "The number " << num << " was found " << totalDuplicateNums << " times in Vector 1. " << endl; //report to user how many times the number was found
    showflow("Exiting Binary Search");
} //binarySearch

//removeDuplicates
void removeDuplicates() {
    showflow("Removing Duplicates");
    for(int i = 0; i < randomNumbers.size(); i++) { //go through the vector starting from the beginning
        int currentNumber = randomNumbers.at(i); //set the value of the iterator to the variable current number
        for(int j = i+1; j < randomNumbers.size(); j++) { //go through the vector starting 1 index over from the first element
            int nextNumber = randomNumbers.at(j); //set the value of this iterator to the adjacent number
            if(currentNumber == nextNumber) { //if the current number is equal to the adjacent number
                randomNumbers.erase(randomNumbers.begin() + j); //then remove the adjacent number to eliminate duplicates
                j--; //decrement to keep indices in order
            } else { //if the current number is not equal to the adjacent number
                break; //then leave and don't do anything
            }
        }
    }
    cout << "\n\nAfter removing duplicates, here are the numbers in Vector 1: " << endl; //report the vector to the user without duplicates
    displayVector(randomNumbers); //show the user the modified vector
    showflow("Removed Duplicates");
} //removeDuplicates

//Main
int main() {
    getUserInput();
    generateRandomNumbers();
    sortTheRandomNumbers();
    bubbleSort();
    for(int i = 0; i < 3; i++) { //prompt the user to search for a number 3 times
        binarySearch();
    }
    removeDuplicates();
    cout << "\nThat is the end of the Sort and Search program. Hope you had fun! Goodbye!";
} //Main
