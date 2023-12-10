
#include "Questions.h"



int Q1_for(int num){
	int sum = 0;
	//exaple; 12 MUIPLES: 12, 24, 36.... till 1000.
	// calculate your sum below..this has to use for loop
	//initial variables
	int i;
	int multiples = 1;
	for (i = 1; num * i < 1000; i++){//check if the multiple is not greater than 1000.
		multiples = num * i; //multiples next multiple.
		sum += multiples; //adds to sum the multiple.
	}
	// here, we return the calcualted sum:
	return sum;
}
int Q1_while(int num){
	int sum = 0;
	// calculate your sum below..this has to use while loop
	int i =1;
	int multiples = 1;
	while(num * i < 1000){ //check if the multiple is not greater than 1000.
		multiples = num * i; //multiples next multiple.
		sum += multiples; //adds to sum the multiple.
		i++; //next factor for the multiples.
	}

	// here, we return the calcualted sum:
	return sum;
}
int Q1_dowhile(int num){
	int sum = 0;
	
	// calculate your sum below..this has to use do-while loop
	//initial variables
	int i = 1; 
	int multiples = 1;
	do {
		multiples = num * i; //multiples next multiple.
		sum += multiples; //adds to sum the multiple.
		i++; //next factor for the multiples.
	}

	while(num * i < 1000); //check if the multiple is not greater than 1000.
	
	// here, we return the calcualted sum:
	return sum;
}
//===============================================================================================
int Q2_FPN(float Q2_input, float Q2_threshold){
	
	int result;
	// Determine which range does Q2_input fall into.  Keep in mind the floating point number range.
	// Assign the correct output to the result.
	if (Q2_input >= -2*Q2_threshold && Q2_input < -1*Q2_threshold){
		result = 0;
	}
	else if (Q2_input >= -1*Q2_threshold && Q2_input < 0){
		result = 1;
	}
	else if (Q2_input >= 0 && Q2_input < 1*Q2_threshold){
		result = 2;
	}
	else if (Q2_input >= 1*Q2_threshold && Q2_input <= 2*Q2_threshold){
		result = 3;
	}
	else{
		result = -999;
	}
	// Finally, return the result.
	return result;
}
//===============================================================================================
int Q3(int Q3_input, int perfect[]){
	
	
	
		//counts is the variable that should hold the total number of found perfect numbers
		//you should update it within your code and return it at the end
	    int counts=0;
		/*
		*
		*perfect is an array that you need to add into it any perfect number you find
		*which means at the end of this function, the perfect[] array should hold all the found perfect numbers in the range
		*you do not need to return perfect because as stated in lectures arrays are already passed by reference. so, modifying them will 
		*autmoatically reflect in the main calling function.
		*/
		//oh so like say where looping through 10. if the factors are 2,5. there would be no perfect numbers because 2 has no factors to sum and so does 5
		int result = 0;
		int index = 0;
		int sum = 0;
		int fac = 0;
		int i = 0;
		if (Q3_input){
			for (i = 2; i < Q3_input; i++){
				for (fac = 1; fac < i; fac++){
					if (i % fac == 0){
						sum += fac;
					}
				}
				if (sum == i){
					counts ++;
					for (index = 0; index < 100; index++){
						
						if (perfect[index] == 0){
							if (perfect[index] != i){
								perfect[index] = i;
								break;
							}
							
						}
					}
					sum = 0;
				}
				else{
					sum = 0;
				}
			}
		}

	   return counts;

}
//===============================================================================================
int Q4_Bubble(int array[], int size){
	
	// This variable tracks the number of passes done on the array to sort the array.
	int passes = 0;
	// Pseudocode
	// 	1. Given an array and its size, visit every single element in the array up to size-2 (i.e. up to the second last element, omit the last element)
	//  2. For every visited element (current element), check its subsequent element (next element).  
	//     If the next element is smaller, swap the current element and the next element. 
	//  3. Continue until reaching size-2 element.  This is considered One Pass => increment pass count by one.
	//  4. Repeat 1-3 until encountering a pass in which no swapping was done.
	//   -> Sorting Completed.
	int currentElement;
	int nextElement;
	int didyouswap = 0;
	int index = 0;
	while (1){
		for (index = 0; index <= size - 2;index++){
			currentElement = array[index];
			nextElement = array[index + 1];
			if (nextElement < currentElement){
				array[index] = nextElement;
				array[index + 1] = currentElement;
				didyouswap = 1;
			}
		}
		if (didyouswap == 1){
			passes+= 1;
			didyouswap = 0;
		}
		else{
			passes+= 1;
			break;
		}
	}
	// Finally, return the number of passes used to complete the Bubble Sort
	return passes;	
}
