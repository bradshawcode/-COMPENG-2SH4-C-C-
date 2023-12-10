#include <stdio.h>
#include "MacUILib.h"

// PPA2 GOAL: 
//       Construct the game backbone where the player can control an object 
//       to move freely in the game board area with border wraparound behaviour.

// Watch Briefing Video and Read Lab Manual before starting on the activity!



// PREPROCESSOR CONSTANTS DEFINITION HERE
/////////////////////////////////////////
#define XLENGTH 20
#define YLENGTH 10


// GLOBAL VARIABLE DEFINITION HERE
/////////////////////////////////////////

int exitFlag; // Program Exiting Flag - old stuff

// For storing the user input - from PPA1
char input;
// [TODO] : Define objPos structure here as described in the lab document

struct objPos{
    int x;
    int y;
    char symbol;
};

// [TODO] : Define the Direction enumeration here as described in the lab document
//          This will be the key ingredient to construct a simple Finite State Machine
//          For our console game backbone.

enum DirState {LEFT, RIGHT, UP, DOWN};
char gameboard[XLENGTH][YLENGTH];
struct objPos player;
enum DirState movestate;
int pressed;
// FUNCTION PROTOTYPING DEFINITION HERE
/////////////////////////////////////////

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// You may insert additional helper function prototypes below.
// 
// As a good practice, always insert prototype before main() and implementation after main()
// For ease of code management.
void redrawboard(void);

// MAIN PROGRAM LOOP
/////////////////////////////////////////
// This part should be intuitive by now.
// DO NOT TOUCH


int main(void)
{
    
    Initialize();

    while(!exitFlag)  
    {
        GetInput();

        RunLogic();

        DrawScreen();

        LoopDelay();
    }

    CleanUp();

}


// INITIALIZATION ROUTINE
/////////////////////////////////////////
void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    input = 0; // NULL
    pressed = 0; //Not pressed.
    exitFlag = 0;  // not exiting    
    player.symbol = '@';
    player.x = 9;
    player.y = 4;
    movestate = RIGHT;
    // [TODO] : Initialize more variables here as seen needed.
    //          PARTICULARLY for the structs!!
    //Generation:
    redrawboard();
}


// INPUT PROCESSING ROUTINE
/////////////////////////////////////////
void GetInput(void)
{

    // [TODO]: The most basic asynchronous input collection algorithm is:
    //   1. Check whether there is any unprocessed input character - read the lab manual and see which MacUILib function you need to use.
    //   2. If there is an input character waiting to be processed, get the character and store it as the "command"
    //      - again, read the lab manual to find out which MacUILib function you need to use.
    //   3. If there is no input character to be processed, just don't do anything and move on.
    if (MacUILib_hasChar()){
        input = MacUILib_getChar();
        pressed = 1;
    }
    else{
        pressed = 0;
    }

    // In future project preparation activities and the project itself, you may need to add more input processing logics here.
    // 
    // The guideline for adding more code is that:
    //  - If the raw input itself maps to a more specific command depending on the program logic states, you may have to 
    //    post-process the command here before sending it off to the main program logic.
    //  - We will talk about these later.

}




// MAIN LOGIC ROUTINE - "Think"
// ===============================
// The second action in our program loop is to execute the main program logic.  
// In this routine, we should determine the outcome of the logic using a) current status / state / behaviour of the program, and b) the most recent input
// The outcome of the logic then will be drawn on the screen.
//
// In later activities, we will delve deeper into this design philosophy later in the course - Finite State Machine design principle.
// 
// Let's now think about how we can complete the marquee display logic...

void RunLogic(void)
{
    // [TODO]: Implement the above pseudocode logic
    if (pressed==1 && input == 27){
        exitFlag = 1;
    }
        //rotate.
    
    //add to display string
    if (pressed==1 && (input >= 65 && input <= 122)){
        if (input < 97){ //changes to lowercase if uppercase.
            input = input + 32;
        }
        switch (input){
            case 'w':
                movestate = UP;
                break;
            case 's':
                movestate = DOWN;
                break;
            case 'a':
                movestate = LEFT;
                break;
            case 'd':
                movestate = RIGHT;
                break;
            default:
                break;
        }
    }
    //Mow action.
    switch (movestate){
        case UP:
            player.y--;
            if (player.y < 0){
                player.y = YLENGTH - 1;
            }
            break;
        case DOWN:
            player.y++;
            if (player.y > YLENGTH - 1){
                player.y = 0;
            }
            break;
        case LEFT:
            player.x--;
            if (player.x < 0){
                player.x = XLENGTH - 1;
            }
            break;
        case RIGHT:
            player.x++;
            if (player.x > XLENGTH - 1){
                player.x = 0;
            }
            break;
        default:
            break;
    }
    redrawboard();
}



// SCREEN DRAWING ROUTINE
/////////////////////////////////////////
void DrawScreen(void)
{
    MacUILib_clearScreen();
    // [TODO] : Implement the latest drawing logic as described in the lab manual
    //
    //  1. clear the current screen contents
    
    //  2. Iterate through each character location on the game board
    //     using the nested for-loop row-scanning setup.

    //  3. For every visited character location on the game board
    //          If on border on the game board, print a special character
    //          If at the player object position, print the player symbol
    //          Otherwise, print the space character
    //     Think about how you can format the screen contents to achieve the
    //     same layout as presented in the lab manual

    //  4. Print any debugging messages as seen needed below the game board.
    //     As discussed in class, leave these debugging messages in the program
    //     throughout your dev process, and only remove them when you are ready to release
    //     your code. 
    //Draws board.
    for (int y = 0; y < YLENGTH; y++){
        for (int x = 0; x < XLENGTH; x++){
            MacUILib_printf("%c", gameboard[x][y]);
        }
        MacUILib_printf("\n");
    }

}



// PROGRAM LOOOP DELAYER ROUTINE
/////////////////////////////////////////
void LoopDelay(void)
{
    // Change the delaying constant to vary the movement speed.
    MacUILib_Delay(50000);    
}



// PROGRAM CLEANUP ROUTINE
/////////////////////////////////////////
// Recall from PPA1 - this is run only once at the end of the program
// for garbage collection and exit messages.
void CleanUp(void)
{
    MacUILib_uninit();
}

void redrawboard(void){
    for (int y = 0; y < YLENGTH; y++){
        for (int x = 0; x < XLENGTH; x++){
            if (y == 0 || y == YLENGTH - 1){
                gameboard[x][y] = '#';
            }   
            else if (x == 0 || x == XLENGTH - 1){
                gameboard[x][y] = '#';
            }
            else if (x == player.x && y == player.y){
                gameboard[x][y] = player.symbol;
            }
            else{
                gameboard[x][y] = ' ';
            }
        }
    }
}


