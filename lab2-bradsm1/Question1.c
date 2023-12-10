#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "Questions.h"



void add_vectors(double vector1[],double vector2[],double vector3[],int size)
{
    /*vector3 should store the sum of vector1 and vector2. 
	You may assume that all three arrays have the size equal to the input parameter "size"
	*/
	//write your code below
	int i;
	
	for (i=0;i<size; i++){ //loops size of vector arrays
		vector3[i] = (vector1[i]+vector2[i]);//adds each element of the vector1 and vector 2 arrays and stores it to vector3.
	}
	return vector3;

}

double scalar_prod(double vector1[],double vector2[],int size)
{
	// this is the variable holding the scalar product of the two vectors
    double prod=0;

	//write your code below to calculate the prod value
	int i;
	for (i=0;i<size;i++){
		prod += (vector1[i]*vector2[i]);
	}

	// return the result
    return prod;
}

double norm2(double vector1[], int size)
{
	//this is the variable holding the L2 norm of the passed vector
    double L2;
	double squaresum=0;
	//write your code here
	for (int i = 0; i<size;i++){
		squaresum += vector1[i] * vector1[i];
	}
	L2 = sqrt(squaresum);
	
	//finally, return the L2 norm 
    return L2;
}
