#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisfoodRef)
{
    mainGameMechsRef = thisGMRef;
    foodRef = thisfoodRef;
    myDir = STOP;

    // more actions to be included
    playerPosList = new objPosArrayList();
    playerpostemp.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*');
    playerPosList->insertHead(playerpostemp);

    // no heap member yet - never used new keyword
}


Player::~Player()
{
    // delete any heap members here

    // we can leave it empty for now
}

bool Player::checkFoodConsumption(){
    foodRef->getFoodPos(foodtemp);
    playerPosList->getHeadElement(playerpostemp);
    if (playerpostemp.x == foodtemp.x && playerpostemp.y == foodtemp.y){
        foodRef->generateFood(playerpostemp);
        return true;
    }
    else{
        return false;
    }
}

void Player::increasePlayerLength(){
    playerPosList->getHeadElement(playerpostemp);
    playerPosList->insertHead(playerpostemp);
}

void Player::checkPlayerOffGrid(){
    if(playerpostemp.y <= 0){
        playerPosList->getHeadElement(playerpostemp);
        playerpostemp.y = mainGameMechsRef->getBoardSizeY()-2;
        playerPosList->insertHead(playerpostemp);
        playerPosList->removeTail();
    }
    if(playerpostemp.y >= mainGameMechsRef->getBoardSizeY()){
            playerPosList->getHeadElement(playerpostemp);
            playerpostemp.y = 1;
            playerPosList->insertHead(playerpostemp);
            playerPosList->removeTail();
        }
    if(playerpostemp.x <= 0)
        {
            playerPosList->getHeadElement(playerpostemp);
            playerpostemp.x = mainGameMechsRef->getBoardSizeX()-2;
            playerPosList->insertHead(playerpostemp);
            playerPosList->removeTail();
        }
    if(playerpostemp.x >= mainGameMechsRef->getBoardSizeX())
        {   
            playerPosList->getHeadElement(playerpostemp);
            playerpostemp.x = 1;
            playerPosList->insertHead(playerpostemp);
            playerPosList->removeTail();
        }
}
bool Player::checkSelfCollision(){
    objPos temp;
    objPos head;
    playerPosList->getElement(head, playerPosList->getSize()-1);
    for (int i = 0; i < playerPosList->getSize() -2; i++){
        playerPosList->getElement(temp, i);
        if (head.x == temp.x && head.y == temp.y){
            return true; //Collision.
        }
    }
    return false;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
    // return the reference to the playerPos arrray list
}
void Player::updatePlayerDir()
{
    // PPA3 input processing logic 
    
    char input = mainGameMechsRef->getInput();
    if (input < 97){ //changes to lowercase if uppercase.
            input = input + 32;
    }
    switch(input) 
    {
        case 'w':
            if(myDir != UP)
            {
                myDir = UP;
            }
            break;

        case 'a':
            if(myDir != LEFT)
            {
                myDir = LEFT;
            }
            break;

        case 's':
            if (myDir != DOWN)
            {
                myDir = DOWN;
            }
            break;

        case 'd':
            if(myDir != RIGHT)
            {
                myDir = RIGHT;
            }
            break;
        
        default:
            break;
    }      
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch(myDir) 
    {
        // player wants to move up
        case UP:
            playerPosList->getHeadElement(playerpostemp);
            playerpostemp.y--;
            playerPosList->insertHead(playerpostemp);
            playerPosList->removeTail();
            this->checkPlayerOffGrid();
            if (checkFoodConsumption() == true){
                this->increasePlayerLength();
                mainGameMechsRef->incrementScore();
            }
            break;

        // player wants to move down
        case DOWN:
            playerPosList->getHeadElement(playerpostemp);
            playerpostemp.y++;
            playerPosList->insertHead(playerpostemp);
            playerPosList->removeTail();
            this->checkPlayerOffGrid();
            if (checkFoodConsumption() == true){
                this->increasePlayerLength();
                mainGameMechsRef->incrementScore();
            }
            break;

        // player wants to move left
        case LEFT:
            playerPosList->getHeadElement(playerpostemp);
            playerpostemp.x--;
            playerPosList->insertHead(playerpostemp);
            playerPosList->removeTail();
            this->checkPlayerOffGrid();
            if (checkFoodConsumption() == true){
                this->increasePlayerLength();
                mainGameMechsRef->incrementScore();
            }
            break;

        // player wants to move right
        case RIGHT:
            playerPosList->getHeadElement(playerpostemp);
            playerpostemp.x++;
            playerPosList->insertHead(playerpostemp);
            playerPosList->removeTail();
            this->checkPlayerOffGrid();
            if (checkFoodConsumption() == true){
                this->increasePlayerLength();
                mainGameMechsRef->incrementScore();
            }
            break;
        // default case
        default:
            break;

        

    }
    if (this->checkSelfCollision() == true){
        mainGameMechsRef->setLoseFlag();
    }
}

