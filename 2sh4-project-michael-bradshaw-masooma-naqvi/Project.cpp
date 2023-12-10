#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* myGameMech;
Player* myPlayer; 
objPosArrayList* playerPosListTemp; 
Food* food;

//char gameBoard[myGM->getBoardSizeX, myGM->getBoardSizeY];

// Dr. Chen Video 1
//objPos myPos;

//bool exitFlag;



void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(!myGameMech->getExitFlagStatus() && !myGameMech->getLoseFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // Iteration 0: Adding a few arbitrarily chosen coordinates and symbols
    //myPos.setObjPos(2, 3, '@');

    myGameMech = new GameMechs();//new GameMechs(26, 13); // makes the board size 26 and 13
    food = new Food(myGameMech);
    myPlayer = new Player(myGameMech, food);
    playerPosListTemp = myPlayer->getPlayerPos();
    objPos temp;
    playerPosListTemp->getHeadElement(temp);
    food->generateFood(temp);
}

void GetInput(void)
{
   myGameMech->getInput(); 
   
}

void RunLogic(void)
{
    if(myGameMech->getInput() == 27)
    {
        myGameMech->setExitTrue(); 
    }

    // update the FSM and move the player
    myPlayer->updatePlayerDir(); 
    myPlayer->movePlayer(); 
    myGameMech->clearInput(); // so to not repeatedly process input;  
}

void DrawScreen(void)
{
    
    // getting the player position
    objPos playerTempPos;
    objPos foodTempPos;
    playerPosListTemp = myPlayer->getPlayerPos();
    food->getFoodPos(foodTempPos);
    objPos tempPos;
    bool print = true;
    //for(int i = 0; i < 1000; i++)
    //{
    //    MacUILib_printf("BoardSize: %dx%d, PlayerPos <%d,%d> + %c\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(),
    //    playerTempPos.x, playerTempPos.y, playerTempPos.symbol);

    //    MacUILib_clearScreen();

    //}
    MacUILib_clearScreen();
     
      for(int i = 0; i < myGameMech->getBoardSizeY(); i++){
          for(int j = 0; j< myGameMech->getBoardSizeX(); j++)
          {
                if(i == 0 || i == (myGameMech->getBoardSizeY()-1)|| j == 0 || j == (myGameMech->getBoardSizeX()-1))
                {
                    MacUILib_printf("#");
                }
                else{
                    for (int index = 0; index < playerPosListTemp->getSize(); index++){
                        playerPosListTemp->getElement(tempPos, index);
                        if(tempPos.y == i && tempPos.x == j)
                        {
                            MacUILib_printf("%c",tempPos.symbol);
                            print = false;
                            break;
                        }
                        else{
                            print = true;
                        }
                    }
                    if (print == true){
                        if (foodTempPos.y == i && foodTempPos.x == j)
                        {
                            MacUILib_printf("%c",foodTempPos.symbol);
                            print = false;
                            
                        }
                        else{
                            MacUILib_printf(" ");
                            print = false;
                        }
                    }
                }

              }
              MacUILib_printf("\n");  
              
          }
          MacUILib_printf("\n");   

    MacUILib_printf("Score: %d\n", myGameMech->getScore());
    MacUILib_printf("Player Pos: [%d %d]\n", tempPos.x, tempPos.y);
    MacUILib_printf("FOOD Pos: [%d %d]\n", foodTempPos.x, foodTempPos.y);
    MacUILib_printf("To exit the game, press the ESC button!");
    

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();   

    if (myGameMech->getExitFlagStatus())
    {
         MacUILib_printf("\nYou pressed ESC. Closing the program..."); 
    } 

    else if (myGameMech->getLoseFlagStatus())
    {
         MacUILib_printf("\nYOU LOST. Game is over...\n"); 
         MacUILib_printf("SCORE: %d", myGameMech->getScore()); 
         myGameMech->setExitTrue();
    } 
  
    MacUILib_uninit();
    delete myGameMech;
    delete myPlayer; 
}
