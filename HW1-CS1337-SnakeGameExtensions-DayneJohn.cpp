// SnakeGame - Orig from the Web
// Dayne John - CS1337.003
// Original code by N. Vitanovic
// see his YouTube video here: https://bit.ly/29WZ5Ml
// Changelog:
//  01/26/2021 - Dayne
//      improved spacing of program
//      reorganized the functions and gave more self-explanatory names to the functions
//  01/27/2021 - Dayne
//      added more comments to clarify each function's purpose
//      separated each function for their individual specific purpose
//  01/28/2021 - Dayne
//      had a bug where the snake was misaligned
//      fixed the game to where it ends when a snake hits a wall
//  01/29/2021 - Dayne
//      fixed the snake misalignment bug
//      got rid of the logic function
//      changed it to where the game ends when a snake hits a wall
//  02/03/2021 - Dayne
//      created a function that shows the locations of the fruits and the snake
//      created a function that generates fruits into their locations
//      had a bug where duplicate fruits were generated
//  02/04/2021 - Dayne
//      fixed duplicate fruit bug
//      created game instructions
//  02/06/2021 - Dayne
//      added more comments inside of each function
//      added an option for the user to restart the game after they fail
//  02/07/2021 - Dayne
//      fixed a bug that generated the tail in the top left of the screen every time the snake ate a fruit
//      made the wall option function more concise and easier to follow/understand
//  02/08/2021 - Dayne
//      made the game instructions easier to understand
//      changed the color of the console and game environment
//  notes:
//      In this version of the game, there are multiple fruits in different locations
//      In a future version, we could change the appearance of this game environment
//		The reason I changed the game to where the snake dies by hitting a wall is to make the game more challenging
//      The user can press 'I' on their keyboard to hide the locations of the fruits and snake in order to improve
//      the quality
//      of the game environment
//      The user can press 'P' on their keyboard to pause the game. They can also press 'X' or 'Q' to quit the game
//      The user can also press 'R' after failing or accidentally quitting in order to play again
#include <iostream>
#include <conio.h> //for kbhit and getch
#include <windows.h>

using namespace std;

//Prototypes
void showFruitLocations();
void showSnakesLocation();


const int width = 20; //width of the board
const int height = 20; //height of the board
int snakeX, snakeY, score; //x and y coordinate of the snake and score
int tailX[100], tailY[100];
int tailLength; //length of the snake's tail
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

int numOfFruits = 5;
const int maxFruits = 100; //maximum number of fruits
int fruitX[maxFruits], fruitY[maxFruits]; //x and y coordinates of the fruits
int count = 0;

bool gameOver = false; //indicates when the user fails
bool gameInfo = true;  //indicates when the location of the fruits and snake are displayed
bool dieIfSnakeHitsWall = false; //indicates if the user dies when the snake hits the wall

//*************************a*********************//
bool showflowControl = false; //debugging switch to make the program talk to me

//showflow
void showflow(string msg) {
    if (showflowControl)
        cout << "--- at: " << msg << endl;
} //showflow


//showScore
void showScore() {
    cout << "Score:" << score << endl;
} //showScore

//displayGameInstructions
void displayGameInstructions() {
    system("COLOR 0B"); //change the color of the instructions
    cout << "Welcome to the Snake Game! Use W A S D to move in order to eat the fruits. " << endl <<
         "Press P to pause the game. Press I to hide the locations/coordinates of the fruits and the snake. " << endl <<
         "Press X or Q at any time to quit the game." << endl;
    system("pause"); //wait for the user to hit a key before continuing
} //displayGameInstructions

//showTheGameInfo
void showTheGameInfo() {
    if(gameInfo == true) {
        showFruitLocations();
        showSnakesLocation();
    }
} //showTheGameInfo


//generateFruitLocations
void generateFruitLocations(int i) {
    int x = rand() % width;
    int y = rand() % height;

    for(int n = 0; n < numOfFruits; n++) {
        while(fruitX[n] == x && fruitY[n] == y) {
            x = rand() % width;
            y = rand() % height;
        }
    }
    fruitX[i] = x;
    fruitY[i] = y;
} //generateFruitLocations


//askUserAboutWallOption
void askUserAboutWallOption() {
    char userChoice;
    cout << "\nWould you like to die if you hit a wall?" << endl; //ask user
    cout << "Enter Y if you want to die when you hit a wall, otherwise enter N." << endl;
    cin >> userChoice; //store response in userChoice

    userChoice = (tolower(userChoice)); //make userChoice case insensitive
    while(userChoice != 'y' && userChoice != 'n') {
        cout << "That is not an appropriate response."; //input validation
        cout << "Enter Y if you want to die when you hit a wall, otherwise enter N." << endl; //ask again
        cin >> userChoice; //store response in userChoice
        userChoice = (tolower(userChoice)); //make userChoice case insensitive
    }

    //if yes then user dies when snake hits wall, but if no user does not die when snake hits wall
    if(userChoice == 'y') {
        dieIfSnakeHitsWall = true;
    } else if(userChoice == 'n') {
        dieIfSnakeHitsWall = false;
    }
}//askUserAboutWallOption



//getUserInput
void getUserInput() {
    cout << "\nHow many fruits do you want to generate? You can generate from 2 to 5 fruits." << endl; //ask the user how many fruits they want
    cin >>  numOfFruits; //store input in numOfFruits

    //make sure input is valid and within the range
    while(numOfFruits > 5 || numOfFruits < 2) {
        cout << "\nPlease enter any number from 2 to 5. How many fruits do you want to generate? " << endl; //ask again
        cin >> numOfFruits; //store input in numOfFruits
    }

} //getUserInput


//Setup
void Setup() {
    showflow("Setup");
    system("COLOR 0a"); //change the color of the board
    gameOver = false; //game is not over
    tailLength = 0; //reset tail length to 0
    dir = STOP;

    //start the game with the snake in the center
    snakeX = width / 2;
    snakeY = height / 2;
    for(int i = 0; i < numOfFruits; i++) {
        fruitX[i] = rand() % width;
        fruitY[i] = rand() % height;
    }
    score = 0;
    showflow("exiting Setup");
} //Setup

//showFruitLocations
void showFruitLocations() {
    showflow("Fruit locations are as follows:");

    cout << "Fruit locations are as follows: " << endl; //display the fruit coordinates

    //display the fruit coordinates if the user chooses to
    if(gameInfo = true) {
        for (int j = 0; j < numOfFruits; j++) {
            cout << "[" << fruitX[j] + 1 << "]" << " " << "[" << fruitY[j] + 1 << "]" << endl;
        }
    }
} //showFruitLocations


//showSnakesLocation
void showSnakesLocation() {
    cout << "Snake is at location: " << "[" << snakeX + 1 << "] " << "[" << snakeY + 1 << "]" << endl; //display the snake's coordinates
} //showSnakesLocation

//DrawTheGameEnvironment
void DrawTheGameEnvironment() {
    showflow("DrawTheGameEnvironment");
    system("cls"); //system("clear");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = -1; j < width + 1; j++) {
            if (j == -1 || j == width)
                cout << "#";
            else if (i == snakeY && j == snakeX)
                cout << "O";
            else {
                bool print = false;

                for(int k = 0; k < numOfFruits; k++) {
                    if (i == fruitY[k] && j == fruitX[k]) {
                        cout << "F";
                        print = true;  //print out a fruit
                        break;
                    }
                }
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
} //DrawTheGameEnvironment

//ControlTheGame
void ControlTheGame() {
    char usersInput;
    showflow("ControlTheGame");
    if (_kbhit()) {
        //did the user hit the keyboard?
        switch (tolower(_getch())) {
        case 'a':
            dir = LEFT;      //move the snake to the left
            break;
        case 'd':
            dir = RIGHT;     //move the snake to the right
            break;
        case 'w':
            dir = UP;        //move the snake upwards
            break;
        case 's':
            dir = DOWN;      //move the snake downwards
            break;
        case 'x':
            gameOver = true; //end the game
            break;
        case 'q':
            gameOver = true; //end the game
            break;
        case 'p':
            system("pause"); //pause the game
        case 'i':
            if(count % 2 == 0) {
                gameInfo = false;
            } else {
                gameInfo = true;
            }
            count++;
            break;
        }
    }
} //ControlTheGame

//updateTheSnakesTail
void updateTheSnakesTail() {
    showflow("updateTheSnakesTail");

    //increase tail length after a snake eats a fruit
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = snakeX;
    tailY[0] = snakeY;
    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
} //updateTheSnakesTail

//shiftTheSnakesHead
void shiftTheSnakesHead() {
    showflow("shiftTheSnakesHead");

    //control the snake
    switch (dir) {
    case LEFT:
        snakeX--;
        break;
    case RIGHT:
        snakeX++;
        break;
    case UP:
        snakeY--;
        break;
    case DOWN:
        snakeY++;
        break;
    default:
        break;
    }
}  //shiftTheSnakesHead


//checkToSeeIfSnakeHitAWall
void checkToSeeIfSnakeHitAWall() {
    showflow("checkToSeeIfSnakeHitAWall");

    //if the snake hits a wall
    if(snakeX > width - 1 || snakeX < 0 || snakeY > height - 1 || snakeY < 0) {
        if(dieIfSnakeHitsWall == true) {
            gameOver = true; //end the game
            cout << "You hit a wall!" << endl;
        }
    }
    if (snakeX >= width)
        snakeX = 0;
    else if (snakeX < 0)
        snakeX = width - 1;
    else if (snakeY >= height)
        snakeY = 0;
    else if (snakeY < 0)
        snakeY = height - 1;

} //checkToSeeIfSnakeHitAWall

//checkToSeeIfSnakeHitItsTail
void checkToSeeIfSnakeHitItsTail() {
    showflow("checkToSeeIfSnakeHitItsTail");

    for (int i = 0; i < tailLength; i++) {  //if the snake hits its own tail
        if (tailX[i] == snakeX && tailY[i] == snakeY) {
            gameOver = true; //end the game
            cout << "You hit your own tail!" << endl; //report this to the user
        }
    }
} //checkToSeeIfSnakeHitItsTail

//checkToSeeIfSnakeAteAFruit
void checkToSeeIfSnakeAteAFruit() {
    showflow("checkToSeeIfSnakeAteAFruit");

    //if the snake eats a fruit
    for (int i = 0; i < numOfFruits; i++) {
        if (snakeX == fruitX[i] && snakeY == fruitY[i]) {
            score += 10; //add 10 points to score
            generateFruitLocations(i); //generate new fruit after a fruit has been eaten
            tailLength++;  //increase tail length
        }
    }
} //checkToSeeIfSnakeAteAFruit

//main
int main() {
    char userRestart;
    displayGameInstructions();
    getUserInput();
    askUserAboutWallOption();
    do {
        Setup();
        while (!gameOver) {
            DrawTheGameEnvironment();
            ControlTheGame();
            checkToSeeIfSnakeAteAFruit();
            updateTheSnakesTail();
            shiftTheSnakesHead();
            checkToSeeIfSnakeHitAWall();
            checkToSeeIfSnakeHitItsTail();
            showScore();
            showTheGameInfo();
            Sleep(100); //change the speed/difficulty of the game
        }
        cout << "Game Over! Do you want to play again? Press R to restart or any other key to quit. "; //ask user if they want to play again
        cin >> userRestart; //store response in userRestart
    } while(tolower(userRestart) == 'r');

    return 0;
} //main
