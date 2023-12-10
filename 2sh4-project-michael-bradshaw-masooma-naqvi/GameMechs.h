#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;

        // additional variables that need to be added
        bool loseFlag;
        int score;
        
        int boardSizeX;
        int boardSizeY;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        bool getExitFlagStatus();
        void setExitTrue();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        void setLoseFlag();
        int getScore();
        void incrementScore();
        bool getLoseFlagStatus();




      

};

class Food{
    private:
        objPos foodPos;
        int active = 0;
        GameMechs* mainGameMechsRef;
    public:
        Food(GameMechs* thisGMRef);
        ~Food();
        void generateFood(objPos blockoff);
        void getFoodPos(objPos &returnPos);
        
};

#endif