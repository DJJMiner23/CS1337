//Dayne John - CS1337.003
//Word Search

//changelog:
//  02/20/2021 - Dayne
//  setup the program to read the file and store the array
//  created a method to display the word search puzzle array
//  set up the arrays for rows and columns and for all 8 directions
//  02/21/2021 - Dayne
//  created a function that skips any comments or blank lines in the file
//  created a function that reports at what coordinates the words were found
//  02/22/2021 - Dayne
//  had a bug where the words were reported multiple times
//  fixed the words reporting bug
//  02/23/2021 - Dayne
//  fixed the program to where it reports the direction that word was found
//  separated reading the dimensions of the array into one function
//  02/24/2021 - Dayne
//  improved spacing of the program
//  reorganized the order of the functions
//  02/25/2021 - Dayne
//  have an issue where it only reports words without spaces
//  created a function that removes the spaces from words and that
//  fixed that issue, now it reports all of the words
//  found a bug where there is a blank line before "Couldn't find these movies:" gets printed
//  02/28/2021 - Dayne
//  improved variable and function names to be more self-documenting
//  changed the color of the console and game environment
//  improved spacing of program
//  02/29/2021 - Dayne
//  fixed the blank line bug before "Couldn't find these movies:" gets printed
//  03/02/2021 - Dayne
//  added custom search ability

//  notes:
//  this program will read in a text file that contains a 2D array and conduct a word search and report
//  where each word was found and the direction that it was found
//  *before searching the matrix, the program checks to see if the words are within the bounds of the matrix and assumes that they aren't in the matrix*
//  *this program has the ability to do a custom search for a word based on user input*

#include <fstream> //for file reading
#include <vector>  //for .push_back
#include <conio.h> //for console output and input
#include <string> //for erase() function
#include <iostream> //for input and output
#include <algorithm> //for the remove() function
using namespace std;

//Variables
string dataFileName = "ComedyMovies-FINAL2.TXT"; //hardwired file name but it will re-prompt the user if you change this name
ifstream infile; //used for file reading
const int maxRows = 100; //maximum number of rows allowed
const int maxColumns = 100; //maximum number of columns allowed
char wordPuzzle[maxRows][maxColumns]; //creating the matrix with a maximum amount 100 rows and 100 columns
int numRows;
int numColumns;
vector<string> missingWords; //vector to store the word that were not found
int specificDirection; //the direction in which the word was found
int xdirection[] = {-1, -1, -1, 0, 1, 1,  1,  0}; //these matrices are used to look for the words in all the directions
int ydirection[] = {-1,  0,  1, 1, 1, 0, -1, -1};
string namesOfDirections[] = {"NW", "N", "NE", "E", "SE", "S", "SW", "W"};
//**********************************************//
//bool showflowControl = false; used this for debugging to make the program talk to me

/* Showflow
void showflow(string msg) {
    if (showflowControl) {
        cout << "--- at: " << msg << endl;
    }
}

void showflow(string msg,string msg2) {
    if (showflowControl) {
        cout << "--- at: " << msg << ", " << msg2 << endl;
    }
}
*/

//openTheFile
bool openTheFile(ifstream &infile,string fileName) {
    //showflow("Opening the file");
    infile.open(fileName); //open the file
    system("COLOR 0B"); //change the color of the output
    if (infile.good()) { //if it opens correctly then continue
        return true;
    } else {
        cout << ("We were not able to find that file."); //otherwise prompt the user again
        cout << "The file name you entered was: " << fileName << endl; //display file name that user entered
        cout << "Enter another file name to use (or press 'q' to quit): "; //let the user enter in another valid file name or quit
        getline(cin, fileName);
        if (fileName != "q") {
            cout << "The file name you entered was: " << fileName << endl; //display file name that was entered
            bool didTheFileOpen = openTheFile(infile,fileName); //check if the file opened
            return didTheFileOpen;
        } else {
            cout << "Exiting program. " << endl; //otherwise quit
            return false;
        }
    }
} //openTheFile

//showMissingWords
void showMissingWords(vector<string> missingWords) {
    //showflow("Missing Words");
    for(string x: missingWords) {
        cout << x << endl; //show the words that were not found
    }
    //showflow("Missing Words");
} //showMissingWords

//skipCommentsOrBlankLines
void skipCommentsOrBlankLines(ifstream &infile) {
    //showflow("Skip Comments");
    string textLine;
    char c;
    c = infile.peek();
    while(c == '#' || c == '\n') { //checks to see if next line is a comment or new line
        getline(infile, textLine);
        c = infile.peek();
    }
    //showflow("skipped all comments.");
} //skipCommentsOrBlankLines

//readTheDimensions
void readTheDimensions() {
    //showflow("Reading the Dimensions");
    if(infile.good()) {
        skipCommentsOrBlankLines(infile);
        infile >> numRows >> numColumns; //read and store the dimensions of the matrix
    }
    //showflow("Read the Dimensions sucessfully");
} //readTheDimensions

//readTheMatrix
void readTheMatrix() {
    //showflow("Reading the Matrix");
    for (int j = 0; j < numRows; j++) { //read in the matrix
        skipCommentsOrBlankLines(infile);
        for (int k = 0; k < numColumns; k++) {
            infile >> wordPuzzle[j][k]; //store this matrix inside of wordPuzzle
        }
    }
    //showflow("Read Matrix successfully");
}//readTheMatrix

//displayTheMatrix
void displayTheMatrix() {
    //showflow("displayingMatrix");
    cout << "Number of Rows: " << numRows << ";  Number of Columns: " << numColumns << ";" << endl; //display the number of rows & columns
    cout << "\nWord Search:" << endl;
    for (int i = 0; i < numRows; i++) {
        for(int j = 0; j < numColumns; j++) {
            cout << wordPuzzle[i][j]; //go through the rows and columns and display the wordPuzzle
        }
        cout << endl;
    }
    cout << "\nFound these Movies: " << endl; //report the words that were found
    //showflow("displayed the Matrix");
}//displayTheMatrix

//removeAllSpaces
string removeAllSpaces(string spacelessWord) {
    //showflow("Removing all spaces");
    spacelessWord.erase(remove(spacelessWord.begin(), spacelessWord.end(), ' '), spacelessWord.end()); //read the entire word and remove any spaces yeah after it reports all of the ones that weren't found and the ones that were found i want to prompt the user to type in a word and report it if it was found the same way
    //showflow("Removed all spaces");
    return spacelessWord;
}//removeAllSpaces

//searchThePuzzle
bool searchThePuzzle(int row, int column, string word) {
    //showflow("Searching the puzzle");
    int length = word.length(); //gets the length of the word
    if(wordPuzzle[row][column] != word[0]) { //check if the first letter of the word doesn't match the first letter in the array
        return false;
    }
    for(int direction = 0; direction < 8; direction++) { //look in all of the 8 directions for the word
        int rowDirection = row + xdirection[direction], columnDirection = column + ydirection[direction];
        int n; //used to look for the word in this particular direction
        for(n = 1; n < length; n++) {
            if(rowDirection >= numRows|| rowDirection < 0 || columnDirection >= numColumns || columnDirection < 0) { //check to see if word is in the bounds of the matrix
                break; //then leave
            }
            if (wordPuzzle[rowDirection][columnDirection] != word[n]) { //if word doesn't match
                break; //then leave
            }
            rowDirection += xdirection[direction], columnDirection += ydirection[direction]; //move vertically and horizontally
        }
        if(n == length) { //if the word matched then store the direction
            specificDirection = direction; //store the direction
            return true;
        }
    }
    //showflow("Searched the puzzle.");
    return false;
} //searchThePuzzle

//wordSearch
bool wordSearch(string word) {
    //showflow("At wordSearch");
    string multipleWords = removeAllSpaces(word); //get rid of the spaces before searching for the words
    string wordsNotFound = word; //used for that words that weren't found
    if(word[0] == '#' || word[0] == '\n') {  //to skip any comments or blank lines
        return false;
    }
    for(int row = 0; row < numRows; row++) {
        for(int column = 0; column < numColumns; column++) {
            if(searchThePuzzle(row, column, multipleWords)) { //if the words were found
                cout << word + " found at " << row + 1 << ", "  << column + 1 << ":\t(direction = " << namesOfDirections[specificDirection] << ")" << endl; //then report at what coordinates and what direction the word was found
                return true;
            }
        }
    }
    missingWords.push_back(wordsNotFound); //store the words that were not found in the missingWords vector
    //showflow("Exiting wordSearch");
    return false;
} //wordSearch

//customSearch
void customSearch() {
    char response; //user response
    bool wordFound; //was the word found
    string customWord; //word that the user entered
    cout << "\nWould you like to search for a word?" << endl; //prompt user
    cout << "Enter y if you want to search for a word." << endl;
    cin >> response; //store response
    response = (tolower(response)); //make response case-insensitive
    cout << "\nWhat word would you like to search for?" << endl; //ask user for word
    cin >> customWord; //store word
    while(response == 'y') {             //if user wants to search for a custom word
        for(int i = 0; i < customWord.size(); i++) {
            customWord.at(i) = toupper(customWord.at(i)); //make word case-insensitive
        }
        wordFound = wordSearch(customWord); //if the word was found then report that it was found
        if(!wordFound) {            //if word was not found
            cout << "\nThe word " << customWord << " was not found" << endl;   //report to user
        }
        cout << "\nDo you want to search for another word?" << endl; //re-prompt user
        cout << "Enter y if you want to search for another word, otherwise press n to exit." << endl;
        cin >> response;
        if(response != 'y') {
            cout << "\nGoodbye!";
            break; //leave
        }
        cout << "\nWhat word would you like to search for?" << endl;
        cin >> customWord;
    }
} //customSearch

//Main
int main() {
    if(openTheFile(infile, dataFileName)) {
        readTheDimensions();
        readTheMatrix();
        displayTheMatrix();
        string hiddenWord;
        while(infile.good()) {
            skipCommentsOrBlankLines(infile);
            if(!infile.eof()) {
                getline(infile, hiddenWord);
                wordSearch(hiddenWord);
            }
        }
        cout << "\n\nCouldn't find these movies: " << endl;
        showMissingWords(missingWords);
    }
    customSearch();
}//Main
