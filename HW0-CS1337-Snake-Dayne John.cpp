// SnakeGame - Orig from the Web
// Dayne John - CS1337.003
// Original code by N. Vitanovic
// see his YouTube video here: https://bit.ly/29WZ5Ml
// changelog:
//  01/26/2021 - Dayne
//      improved spacing of program
//      reorganized the functions and gave more self-explanatory names to the functions
//  01/27/2021 - Dayne
//      added more comments to clarify each function's purpose
//      separated each function for their individual specific purpose
//  01/28/2021 - Dayne
//      had a bug where the snake misaligned and the borders were moving and unstable
//      fixed the game to where it ends when a snake hits a wall
//  01/29/2021 - Dayne
//      fixed the snake misalignment/border bug
//      got rid of the logic function
//      changed it to where the game ends when a snake hits a wall

//  notes:
//      in the future, we could add more fruits in multiple locations
//      we could also change the appearance of a fruit


#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

//**********************************************//


void SetUpTheGame() //set up the game
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
} //set up the game
void DrawTheGameBoard() //draw the game board
{
    system("cls"); //system("clear");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
             if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }


    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
    //draw the game board
}

void ControlTheSnake() //control the snake
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        case 'p':
             dir = STOP;
              if (!'p')
               gameOver = false;
                break;
        }
    } //control the snake
}

void updateTheSnakesTail()     //update the snake's tail
{

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
}   //update the snake's tail

void shiftTheSnakesHead()    //shift the snake's head
{
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
}  //shift the snake's head

void checkToSeeIfSnakeHitAWall() //see if snake hits wall
{
    if (x > width || x < 0 || y > height || y < 0)
    gameOver = true; //end game
} //see if snake hits wall

void checkToSeeIfSnakeHitItsTail() //see if snake hits tail
{
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true; //end game
} //see if snake hits tail
void checkToSeeIfSnakeAteAFruit()
{
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    SetUpTheGame();
    while (!gameOver)
    {
        DrawTheGameBoard();
        ControlTheSnake();
        updateTheSnakesTail();
        shiftTheSnakesHead();
        checkToSeeIfSnakeHitAWall();
        checkToSeeIfSnakeHitItsTail();
        checkToSeeIfSnakeAteAFruit();
        Sleep(10); //sleep(10);
    }
    system("pause");
    return 0;
}
