#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    // default board size
    boardSizeX = 30;
    boardSizeY = 15;
    score = 0;

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    // default board size
    boardSizeX = boardX;
    boardSizeY = boardY;
    score = 0;

}

// do you need a destructor?
// need to add one later

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar()){

        //Obtain/assign
        input = MacUILib_getChar();
    
    }

    return input;

}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

Food::Food(GameMechs* thisGMRef){
    mainGameMechsRef = thisGMRef;
}

Food::~Food(){
}

void Food::generateFood(objPos blockOff){
    int randomX = 0;
    int randomY = 0;
    srand(time(NULL)); //seed with time
    bool flag = true;
    while (flag){
        randomX = (rand() % (mainGameMechsRef->getBoardSizeX() - 2)) + 1;
        randomY = (rand() % (mainGameMechsRef->getBoardSizeY() - 2)) + 1;
        if (randomX == blockOff.x && randomY == blockOff.y){
            flag = true;
        }
        else{
            flag = false;
        }
    }
    foodPos.setObjPos(randomX, randomY, 'A');
    active = 1; //Meaning that this food is in use.
}
void Food::getFoodPos(objPos &returnPos){
    foodPos.getObjPos(returnPos);
}