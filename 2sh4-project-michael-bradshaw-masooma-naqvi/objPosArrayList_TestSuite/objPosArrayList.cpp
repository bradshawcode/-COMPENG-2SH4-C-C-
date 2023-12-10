#include "objPosArrayList.h"
#include <stdexcept>

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; // 200 elements on the heap
    listSize = 0;                      // no valid element in the list upon start up
    arrayCapacity = ARRAY_MAX_CAP;     // array capacity is max

}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; // remember to use delete[] to call the destructors of all instances in the array
                    // otherwise, only the first element will be properly deleted, leading to leak
}       

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // error checking: throw std exception handling
    if(listSize == arrayCapacity)
    {
        throw std::out_of_range("The array list is full.");
    }

    // shuffle all the elements toward the tail
    for(int i = listSize; i > 0; i--)
    {
        aList[i].setObjPos(aList[i-1]);
    }

    // sets the value at first index 
    aList[0].setObjPos(thisPos);

    // increases the size of the list
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // error checking: throw std exception handling
    if(listSize == arrayCapacity)
    {
        throw std::out_of_range("The array list is full.");
    }

    // set the indicated value as the last element
    aList[listSize] = thisPos;

    // increase the size of the list
    listSize++;

}

void objPosArrayList::removeHead()
{
    // error checking: throw std exception handling
    if(listSize == 0)
    {
        throw std::out_of_range("The array list is empty.");
    }

    // shuffle all the elements towards the head
    for(int i = 0; i < listSize -1; i++)
    {
        aList[i] = aList[i+1];
    }

    // decrease the size of the list
    listSize--;
}

void objPosArrayList::removeTail()
{
    // error checking: throw std exception handling
    if(listSize == 0)
    {
        throw std::out_of_range("The array list is empty.");
    }

    // decrease the size of the list
    listSize--;

}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}