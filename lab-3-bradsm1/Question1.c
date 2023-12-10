#include <stdio.h>
#include <stdlib.h>

#include "Questions.h"


int my_strlen(const char * const str1)
{
	int length = 0;
	// Returns the length of the string - the number of characters, but IGNORING the terminating NULL character
	for (length = 0; str1[length] != '\0'; length++);
	return length;
}

int my_strcmp(const char * const str1, const char * const str2)
{
	// Return 0 if the two strings are not identical.  Return 1 otherwise.
	
	// Criteria 1: Check their lenghts.  If not the same length, not equal
	int lengthstr1 = my_strlen(str1);
	int lengthstr2 = my_strlen(str2);
	int i;
	int pass = 0;
	if (lengthstr1 != lengthstr2){
		return 0;
	}
	// Criteria 2: Check their contents char-by-char.  If mismatch found, not equal
	for (i = 0; i < lengthstr1; i++){
		if (str1[i] != str2[i]){
			return 0;
		}
		else{
			pass = 1;
		}
	}
	// if passing the two criteria, strings equal
	if (lengthstr1==lengthstr2){
		return 1;
	}
	if (pass == 1){
		return 1;
	}

}


int my_strcmpOrder(const char * const str1, const char * const str2)
{
	/*compare_str alphabetically compares two strings.
    	If str2 is alphabetically smaller than str1 (comes before str1),
    	the function returns a 1, else if str1 is smaller than str2, the
    	function returns a 0.*/

	// if two strings are completely identical in order, return -1.

	// We are NOT looking for any custom alphabetical order - just use the integer values of ASCII character
	int pass = 0;
	int i;
	int size = 0;
	int lenstr1 = my_strlen(str1);
	int lenstr2 = my_strlen(str1);
	if (lenstr1 > lenstr2){
		size = lenstr2 + 1;
	}
	else if (lenstr2> lenstr1){
		size = lenstr1 + 1;
	}
	else{
		size = lenstr2 + 1;
	}
	for (i = 0; i < size; i++){
		if (str1[i] > str2[i]){
			return 1;
		}
		else if (str1[i] < str2[i]){
			return 0;
		}
		else{
			pass = 1;
		}
	}
	if (pass == 1){
		return -1;
	}
}


char *my_strcat(const char * const str1, const char * const str2){

	/* this is the pointer holding the string to return */
	char *z = NULL;
	
	/*write your implementation here*/
	int lengthstr1 = my_strlen(str1);
	int lengthstr2 = my_strlen(str2);
	int sizeofarray = lengthstr1 + lengthstr2 + 1; //added 1 for null char.
	int i = 0;
	int index = 0;
	z = (char*)calloc(sizeofarray, sizeof(char));
	for (i = 0; i < 2; i++){

		if (i == 0){
			for (index = 0; index < lengthstr1; index++){
				z[index] = str1[index];
			}
		}
		else{
			for (index = 0; index < lengthstr2; index++){
				z[index+lengthstr1] = str2[index];
			}
			z[sizeofarray - 1] = '\0';
		}
	}
	/* finally, return the string*/
	return z;

	// IMPORTANT!!  Where did the newly allocated memory being released?
	// THINK ABOUT MEMORY MANAGEMENT
	
}