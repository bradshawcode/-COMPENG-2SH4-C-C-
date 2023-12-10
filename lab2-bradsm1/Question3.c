#include <stdio.h>
#include <stdlib.h>
#include "Questions.h"


// this is the very first question without hints in the comments.  read the manual to develop your own algorithm

// Read Questions.h to understand the definition of Q3Struct

void efficient(const int source[], struct Q3Struct effVector[], int size)
{
    int k=0;
    for (int i =0; i < size; i++){
        if (source[i] != 0){
            effVector[k].val = source[i];
            effVector[k].pos = i;
            k++;
        }
    }

}

void reconstruct(int source[], int m, const struct Q3Struct effVector[], int n)
{
    int change = 0;
    for (int i =0; i < m; i++){
        for (int j =0;j<n;j++){
            if (effVector[j].pos == i){
                source[i] = effVector[j].val;
                change = 1;
                break;
            }
            else{
                change = 0;
            }
        }
        if (change == 0){
            source[i] = 0;
        }

    }
}
