#include <stdio.h>
#include "MacUILib.h"
#include "myStringLib.h"   // This is your first custom C library
#include <time.h>
#include <stdlib.h>
// [TODO] Import the required library for rand() and srand()
// [TODO] Import the required library for accessing the current time - for seeding random number generation




// PREPROCESSOR DIRECTIVE CONSTANTS
// ================================
#define XLENGTH 20
#define YLENGTH 10
#define MYSTERYARRAYSIZE 13
#define OBJSIZE 5
// For program-wide constants, define them here using #define.  Add as seen needed.

// [COPY AND PASTE FROM PPA2] Copy your additional preprocessor constants from PPA2 and paste them below


// [TODO] Then, define more constants here as seen needed.





// GLOBAL VARIABLES
// ================================

int exitFlag; // Program Exiting Flag
int winFlag;
// [COPY AND PASTE FROM PPA2] Copy your additional global from PPA2 and paste them below

// [TODO] Declare More Global Variables as seen needed.
const char goalString[] = "McMaster-ECE";
// [TODO] Declare Global Pointers as seen needed / instructed in the manual.
char *mysteryString = NULL;
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
struct objPos *itemBin = NULL;
int distanceTravel; //The distance per block traveled/




// FUNCTION PROTOTYPES
// ================================
// Declare function prototypes here, so that we can organize the function implementation after the main function for code readability.

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);
void redrawboard(void);
void populateMystery(void);
void clearitemBin(void);
void collusion(void);
void checkifwin(void);
// [TODO] In PPA3, you will need to implement this function to generate random items on the game board
//        to set the stage for the Scavenger Hunter game.
// list[]       The pointer to the Item Bin
// listSize     The size of the Item Bin (5 by default)
// playerPos    The pointer to the Player Object, read only.
// xRange       The maximum range for x-coordinate generation (probably the x-dimension of the gameboard?)
// yRange       The maximum range for y-coordinate generation (probably the y-dimension of the gameboard?)
// str          The pointer to the start of the Goal String (to choose the random characters from)
void GenerateItems(struct objPos list[], const int listSize, const int xRange, const int yRange);




// MAIN PROGRAM
// ===============================
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
// ===============================
void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    input = 0; // NULL
    pressed = 0; //Not pressed.
    exitFlag = 0;  // not exiting  
    winFlag = 0; //not wiining  
    player.symbol = '@';
    player.x = 9;
    player.y = 4;
    movestate = RIGHT;
    distanceTravel = 0;
    mysteryString = (char*)calloc(MYSTERYARRAYSIZE, sizeof(char));
    itemBin = (struct objPos*)calloc(OBJSIZE, sizeof(struct objPos));
    // [TODO] : Initialize more variables here as seen needed.
    //          PARTICULARLY for the structs!!
    //Generation:
    populateMystery();//generates with ?, except last one which is null.
    clearitemBin();
    GenerateItems(itemBin, OBJSIZE, XLENGTH, YLENGTH);
    redrawboard();
    

    
    // [TODO] Allocated heap memory for on-demand variables as required.  Initialize them as required.

    // [TODO] Seed the random integer generation function with current time.

    // [TODO] Generate the initial random items on the game board at the start of the game.

    
}




// INPUT COLLECTION ROUTINE
// ===============================
void GetInput(void)
{

    // Asynchronous Input - non blocking character read-in
    
    // [COPY AND PASTE FROM PPA2] Copy your input collection routine from PPA2 and paste them below
    if (MacUILib_hasChar()){
        input = MacUILib_getChar();
        pressed = 1;
    }
    else{
        pressed = 0;
    }

    // [TODO] Though optional for PPA3, you may insert any additional logic for input processing.

   
}




// MAIN LOGIC ROUTINE
// ===============================
void RunLogic(void)
{
    // [COPY AND PASTE FROM PPA2] Copy your main logic routine from PPA2 and paste them below
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
            if (player.y <= 0){
                player.y = YLENGTH - 2;
            }
            collusion();
            break;
        case DOWN:
            player.y++;
            if (player.y >= YLENGTH - 1){
                player.y = 1;
            }
            collusion();
            break;
        case LEFT:
            player.x--;
            if (player.x <= 0){
                player.x = XLENGTH - 2;
            }
            collusion();
            break;
        case RIGHT:
            player.x++;
            if (player.x >= XLENGTH - 1){
                player.x = 1;
            }
            collusion();
            break;
        default:
            break;
    }
    redrawboard();
    distanceTravel++;
    // [TODO]   Implement the Object Collision logic here
    //
    //      Simple Collision Algorithm
    //      1. Go through all items on board and check their (x,y) against the player object x and y.
    //      2. If a match is found, use the ASCII symbol of the collided character, and 
    //         find all the occurrences of this ASCII symbol in the Goal String
    //      3. For every occurrence, reveal its ASCII character at the corresponding location in the
    //         Collected String
    //      4. Then, determine whether the game winning condition is met.

    // [TODO]   Implement Game Winning Check logic here
    //
    //      Game Winning Check Algorithm
    //      1. Check if the contents of the Collected String exactly matches that of the Goal String.
    //         YOU MUST USE YOUR OWN my_strcmp() function from Lab 3.
    //      2. If matched, end the game.
    //      3. Otherwise, discard the current items on the game board, and 
    //         generate a new set of random items on the board.  Game continues.
    
}



// DRAW ROUTINE
// ===============================
void DrawScreen(void)
{
    MacUILib_clearScreen();
    // [COPY AND PASTE FROM PPA2] Copy your draw logic routine from PPA2 and paste them below
    //Draws board.
    if (winFlag == 1){
        MacUILib_printf("YOU WIN!!!!!!\nYou Moved at total distance of %d blocks!\nThe Mystery String was ", distanceTravel);
        for (int i = 0; i < MYSTERYARRAYSIZE; i++){
            MacUILib_printf("%c", mysteryString[i]);
        }
        MacUILib_printf(".\n");
    }
    else{
        for (int y = 0; y < YLENGTH; y++){
            for (int x = 0; x < XLENGTH; x++){
                MacUILib_printf("%c", gameboard[x][y]);
            }
            MacUILib_printf("\n");
        }
        // [TODO]   Insert somewhere in the draw routine to draw the randomly generated items on the board.
        // [TODO]   Display the "Mystery String" contents at the bottom of the game board
        //          To help players keep track of their game progress.
        for (int i = 0; i < MYSTERYARRAYSIZE; i++){
            MacUILib_printf("%c", mysteryString[i]);
        }
        MacUILib_printf("\n");
        MacUILib_printf("Move Count: %d", distanceTravel);
    }
}



// DELAY ROUTINE
// ===============================
void LoopDelay(void)
{
    MacUILib_Delay(66666); // smoothness of 60fps
}





// TEAR-DOWN ROUTINE
// ===============================
void CleanUp(void)
{
    // [TODO]   To prevent memory leak, free() any allocated heap memory here
    //          Based on the PPA3 requirements, you need to at least deallocate one heap variable here.
    free(mysteryString);
    free(itemBin);
    // Insert any additional end-game actions here.
    

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
    for (int i = 0; i < OBJSIZE; i++){
        gameboard[itemBin[i].x][itemBin[i].y] = itemBin[i].symbol;
    }
}

void populateMystery(void){
    int i;
    for (i= 0; i < MYSTERYARRAYSIZE; i++){
        if (i == MYSTERYARRAYSIZE - 1){
            mysteryString[i] = '\0';
        }
        else{
            mysteryString[i] = '?';
        }
    }

}

void clearitemBin(){
    for (int i = 0; i < OBJSIZE; i++){
        itemBin[i].x = 0;
        itemBin[i].y = 0;
        itemBin[i].symbol = '\0';
    }
}


void collusion(){
    int changed = 0;
    int index;
    int i;
    for (i= 0; i < OBJSIZE; i++){
        if (itemBin[i].x == player.x){
            if (itemBin[i].y == player.y){
                for (index = 0; index < MYSTERYARRAYSIZE - 1; index++){
                    if (goalString[index] == itemBin[i].symbol){
                        mysteryString[index] = itemBin[i].symbol;
                        changed = 1;
                    }
                }
                MacUILib_Delay(1000);
                break;
            }
            else{
                changed = 0;
            }
        }
    }
    if (changed == 1){
        GenerateItems(itemBin, OBJSIZE, XLENGTH, YLENGTH);
        checkifwin();
        i=0;
    }
}

void checkifwin(){
    int COUNT = 0;
    int i;
    for (i = 0; i < MYSTERYARRAYSIZE -1; i++){
        if (mysteryString[i] == goalString[i]){
            COUNT++;
        }
    }
    if (COUNT == MYSTERYARRAYSIZE - 1){
        exitFlag = 1;
        winFlag = 1;
    }
}

// The Item Generation Routine
////////////////////////////////////
void GenerateItems(struct objPos list[], const int listSize, const int xRange, const int yRange)
{
    // This is possibly one of the most conceptually challenging function in all PPAs
    // Once you've mastered this one, you are ready to take on the 2SH4 course project!
    int randomX;
    int randomY;
    int randomCharIndex;
    char randomChar;
    int sizeofMystery = MYSTERYARRAYSIZE;
    int i = 0;
    int reg = 1;
    int pass = 1;
    int COUNT = 0;  
    int samechar = 0;
    int index;
    srand(time(NULL)); //seed with time
    clearitemBin();
    // Random Non-Repeating Item Generation Algorithm
    ////////////////////////////////////////////////////
    while (reg == 1){
        randomX = (rand() % (xRange - 3)) + 1;
        randomY = (rand() % (yRange - 3)) + 1;
        randomCharIndex = rand() % (sizeofMystery - 1);
        randomChar = goalString[randomCharIndex];
        // if (randomChar == '\0'){
        //     samechar = 1;
        //     break;
        // }
        // else{
        //     samechar = 0;
        // }
        if ((randomX == player.x && randomY == player.y)){
            reg = 1;
            pass = 0;
        }
        else{
            for (index = 0; index < i; index++){
                if (list[index].symbol == randomChar){
                    reg = 1;
                    pass = 0;
                    break;
                }
                else{
                    pass = 1;
                    reg = 1;
                }   
                if ((list[index].x == randomX) && (list[index].y == randomY)){
                    reg = 1;
                    pass = 0;
                    break;
                }
                else{
                    pass = 1;
                    reg = 1;
                }
            }
            
        }
        if (pass == 1){
            list[i].x = randomX;
            list[i].y = randomY;
            list[i].symbol = randomChar;
            i++;
            COUNT++;
        }
        if (COUNT == 5 || i > 4){
            reg = 0;
        }
        else{
            reg = 1;
        }
    }
    
    // Use random number generator function, rand(), to generate a random x-y coordinate and a random choice of character from the Goal String as the ASCII character symbol.
    //      The x and y coordinate range should fall within the xRange and yRange limits, which should be the x- and y-dimension of the board size.
    // This will then be a candidate of the randomly generated Item to be placed on the game board.

    // In order to make sure this candidate is validated, it needs to meet both criteria below:
    //  1. Its coordinate and symbol has not been previously generated (no repeating item)
    //  2. Its coordinate does not overlap the Player's position
    // Thus, for every generated item candidate, check whether its x-y coordinate and symbol has previously generated.  
    //  Also, check if it overlaps the player position
    //      If yes, discard this candidate and regenerate a new one
    //      If no, this candidate is validated.  Add it to the input list[]

    // There are many efficient ways to do this question
    //  We will take a deep dive into some methods in 2SI.

}
