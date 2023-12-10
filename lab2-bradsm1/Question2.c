#include <stdio.h>
#include <stdlib.h>

#include "Questions.h"

void diag_scan(int mat [][N3], int arr [])
{

    // This is the first programming (scripting) question without any initial setup as hints.

    // This is also the first question requiring you to come up with an algorithm on paper 
    // with mathematical analysis before implementing the code.

    // High Level Hint:
    //  Assume a 3x3 square matrix, look at the SUM of the row and column indices of each element.
    //  You should be able to see a numerical pattern after doing so.

    //take a matrix of 3x3 and traform it to a single matrix of 1x9, and scan each element from the start
    //vertically until last element
    int r = 0;
    int c = 0;
    int passes = 0;
    while (passes != (N3*N3)){
        if (r==0 && c==0){
            c +=1;
        }
        else{
            if (c>r+2){
                r = c -2;
                c = c -1; 
            }
            else if (c > r){
                r = c;
                c = r - 1;
            }
            else if (r > c){
                c = r +1;
                r = c - 2;
            }
        }
        passes++;
    }
}
