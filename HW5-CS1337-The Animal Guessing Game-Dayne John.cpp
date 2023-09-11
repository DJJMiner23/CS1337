//Dayne John - CS1337.003
//The Animal Guessing Game

//  changelog:
//  03/29/2021 - Dayne
//      created the program
//      created the struct
//  03/30/2021 - Dayne
//      created the nodes and the pointers to each animalNode
//  03/31/2021 - Dayne
//      created a function to get the yes or no answers from the user
//  04/01/2021 - Dayne
//      created a function to ask the questions and get responses after the computer incorrectly guesses the animal
//      created a function to play the game
//      updated the program to play with new animals each time
//  04/02/2021 - Dayne
//      reorganized the functions and gave more self-explanatory names to the functions
//      created a function to restart the game if the user chooses to play again
//      updated the program to validate user input
//  04/03/2021 - Dayne
//      added more comments to clarify each function's purpose
//  04/05/2021 - Dayne
//      made the program more user-friendly
//      improved the spacing of the program
//  04/06/2021
//      changed the way the program was controlled via do while loop
//  notes:
//      This program is an animal game that asks the user to think of an animal and then asks the user if it's a lizard. After that, the user can choose to keep playing
//      if the computer guessed incorrectly or correctly. If the computer guessed incorrectly, the computer asks for a question that differentiates the animal that the computer guessed
//      and the animal that the user was thinking of. The user inputs that question and types if the answer to that question is yes/no. Based off of this response, the computer gets smarter
//      each time and is able to more accurately guess the animal as the game goes on.
//      This version of the program also has input validation.

#include <iostream> //for input and output
#include <string>   //for .empty() and toupper()
#include <conio.h>  //for _getch

using namespace std;
bool showflowControl = false; //for debugging
//*******************************************************************//

//used this for debugging to make the program talk to me
void showflow(string msg) {
    if (showflowControl) {
        cout << "--- at: " << msg << endl;
    }
}

//animalNode //structure
struct animalNode {
    string question;
    string guess;
    animalNode* yesAnswer;
    animalNode* noAnswer;
}; //animalNode


//createAnimalNode
animalNode* createAnimalNode(string guess) {
    animalNode* node = new animalNode();
    node->question = "";
    node->guess = guess;   //make sure the node that points to the guess is equal to guess
    node->yesAnswer = nullptr; //points to yesAnswer which has null pointers
    node->noAnswer = nullptr;  //points to noAnswer which has null pointers

    return node;

} //createAnimalNode

//getAnswer
void getAnswer(string &guess) {
    showflow("Getting Answer");
    cin >> guess;
    guess[0] = toupper(guess[0]); //change first letter of user input to upper case
    if(!(guess == "Yes" || guess == "No")) {
        cout << "Invalid answer. Please enter Yes or No. "; //validate user input
        getAnswer(guess);
    }
    showflow("Got the Answer");
} //getAnswer


//getInfo
void getInfo (string &guess, string &question, string &userResponse, animalNode* currentNode) {
    showflow("Getting Info");
    cout << "Bummer! What animal were you thinking of? " << endl; //ask the user what the correct animal was
    cin >> guess; //store the correct animal
    cin.ignore(); //ignore next line
    cout << "What is a yes/no question that I can use to tell the difference between a(n) " << guess << " and a(n) " << currentNode->guess << "?" << endl; //
    getline(cin, question);
    cout << "For a(n) " << guess << ", is the answer yes or no?";
    getAnswer(userResponse);
    showflow("Got the Info");
} //getInfo

//playGame
void playGame(animalNode* currentNode) {
    showflow("Playing Game");
    string userResponse; //variable to hold user response
    if(!(currentNode->question.empty())) {
        cout << currentNode->question << endl;
        getAnswer(userResponse);
        if(userResponse == "Yes") {
            playGame(currentNode->yesAnswer);
        } else {
            playGame(currentNode->noAnswer);
        }
    } else {
        cout << "Is it a(n) " << currentNode->guess << "?" << endl; //make the program guess the animal
        getAnswer(userResponse);
        if(userResponse == "Yes") {
            cout << "Awesome, I guessed your animal! \n" << endl;
        } else {
            string guess;
            string question;
            string answer;
            getInfo(guess, question, answer, currentNode);
            animalNode* noNode = NULL; //set noNode pointer to null
            animalNode* yesNode = NULL; //set yesNode pointer to null
            if(answer == "Yes") { //if the user answers yes to the differentiating question
                yesNode = createAnimalNode(guess); //then create a new animal in the system
                noNode = createAnimalNode(currentNode->guess);  //then make the noNode point to the other animal
            } else { //if the user answers no to the differentiating question
                noNode = createAnimalNode(guess);  //then create a new animal in the system
                yesNode = createAnimalNode(currentNode->guess); //and set the yesNode equal to the other animal
            }
            currentNode->guess = "";
            currentNode->question = question; //make the current node point to the question
            currentNode-> yesAnswer = yesNode; //make the current node point to the yesAnswer and set the yesNode equal to this
            currentNode-> noAnswer = noNode; //make the current node point to the noAnswer and set the noNode equal to this
            // cout << " Hi"; debugging statement
        }
    }
    showflow("Played the Game");
} //playGame


//restartGame
bool restartGame() {
    showflow("Restarting Game");
    string userResponse;
    cout << "Do you want to play again? "; //ask user if they want the computer to try again
    cin >> userResponse;
    cout << endl;
    userResponse[0] = toupper(userResponse[0]);


    if(userResponse == "Yes") { //if they do, then restart game
        return true;
    } else {    //otherwise, stop the game and quit
        cout << "Thank you for playing the Animal Guessing Game. Goodbye!"; //user-friendly message
        return false;
    }
    showflow("Game restarted");
} //restartGame

//main
int main() {
    char userInput;
    cout << "Welcome to the Animal Guessing Game! " << endl; //user-friendly message
    cout << "Think of an animal and press enter when you are ready.\n" << endl;
    animalNode* root = createAnimalNode("lizard");
    userInput = _getch(); //get the key that the user pressed
    do {
        while(userInput != '\r') { //make sure user presses the enter key
            cout << "Invalid key pressed. \nPlease press the enter key to continue. " << endl; //if they don't then re-prompt them until they press the enter key
            userInput = _getch();
        }
        playGame(root);
    } while (restartGame());

}//main
