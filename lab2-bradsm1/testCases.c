#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CuTest.h"
#include "Questions.h"
    

    
    
//=========Question 1==================================
void TestQ1_add(CuTest *tc) {

	int n = 5;
	double input1[5] = {3.60, 4.78, 6.00, 10.00, 0.01};
	double input2[5] = {1.50, 2.00, 3.30, 9.90, 1.00};
	double actual[5];
	double expected [5] = {5.10, 6.78, 9.30, 19.90, 1.01};
	add_vectors(input1,input2,actual,n);
	int i;
	for (i=0; i<n; i++)
		CuAssertDblEquals(tc, expected[i], actual[i],0.009);
}

void TestQ1_add2(CuTest *tc) {

	int n = 5;
	double input1[5] = {2.5, 3.33, 4.78, 10.66, 0};
	double input2[5] = {0, 0, 3.1459, 8.88, 104.56};
	double actual[5];
	double expected [5] = {2.5,3.33,7.93,19.54,104.56};
	add_vectors(input1,input2,actual,n);
	int i;
	for (i=0; i<n; i++)
		CuAssertDblEquals(tc, expected[i], actual[i],0.009);
}
   
void TestQ1_scalar_prod(CuTest *tc) {

	int n = 5;
	double input1[5] = {3.60, 4.78, 6.00, 10.00, 0.01};
	double input2[5] = {1.50, 2.00, 3.30, 9.90, 1.00};
	double expected=133.770 ;
	double actual = scalar_prod(input1,input2,n);

	CuAssertDblEquals(tc, expected, actual,0.009);
}

void TestQ1_scalar_prod2(CuTest *tc) {

	int n = 5;
	double input1[5] = {6.66, 4.78, 0, 10.00, 0.44};
	double input2[5] = {0, 3.00, 0, 13.90, 12.00};
	double expected= 158.62;
	double actual = scalar_prod(input1,input2,n);

	CuAssertDblEquals(tc, expected, actual,0.009);
}

void TestQ1_norm(CuTest *tc) {

	int n = 5;
	double input1[5] = {3.60, 4.78, 6.00, 10.00, 0.01};
	double expected=13.108 ;
    double actual = norm2(input1,n);

    CuAssertDblEquals(tc, expected, actual,0.009);
}

void TestQ1_norm2(CuTest *tc) {

	int n = 5;
	double input1[5] = {3.14, 7.33, 6.43, 350.00, 0};
	double expected= 350.149;
    double actual = norm2(input1,n);
    CuAssertDblEquals(tc, expected, actual,0.009);
}
//===========================================================
//=================Question 2================================  

void TestQ2(CuTest *tc) {
	int n = 3;
	int input[3][3] = {{1, 2, 3},{ 5, 8, 9},{ 0, 3, 5}};
	int expected[9]= {1, 2, 5, 3, 8, 0, 9, 3, 5};
	int actual[9];
	diag_scan(input,actual);

	int i;
	for (i=0; i<n*n; i++)
		CuAssertIntEquals(tc, expected[i], actual[i]);
}


    
//===========================================================
//=================Question 3================================   
void TestQ3_1(CuTest *tc) {
	int n=8;
	int input[]={0,0,23,0,-7,0,0,48};
	struct Q3Struct actual[8] = {0};
	struct Q3Struct expected[8] = {{23, 2}, {-7, 4}, {48, 7}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
	efficient(input,actual,n);
    
	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i].val, actual[i].val);
		CuAssertIntEquals(tc, expected[i].pos, actual[i].pos);
	}
}

void TestQ3_2(CuTest *tc) {
	int n=8;
	int input[]={0,33,23,0,-7,0,0,22};
	struct Q3Struct actual[8] = {0};
	struct Q3Struct expected[8] = {{33, 1},{23, 2}, {-7, 4}, {22, 7}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
	efficient(input,actual,n);
    
	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i].val, actual[i].val);
		CuAssertIntEquals(tc, expected[i].pos, actual[i].pos);
	}
}

void TestQ3_3(CuTest *tc) {
	int n=8;
	int input[]={21,22,23,0,-7,0,0,48};
	struct Q3Struct actual[8] = {0};
	struct Q3Struct expected[8] = {{21, 0}, {22, 1}, {23, 2}, {-7, 4}, {48, 7}, {0, 0}, {0, 0}, {0, 0}};
	efficient(input,actual,n);
    
	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i].val, actual[i].val);
		CuAssertIntEquals(tc, expected[i].pos, actual[i].pos);
	}
}

void TestQ3_zeros(CuTest *tc) {
	int n=8;
	int input[]={0,0,0,0,0,0,0,0};
	struct Q3Struct actual[8] = {0};
	struct Q3Struct expected[8] = {0};
	efficient(input,actual,n);
    
	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i].val, actual[i].val);
		CuAssertIntEquals(tc, expected[i].pos, actual[i].pos);
	}
}

void TestQ3_combined(CuTest *tc) {
	int n=8;
	int input[]={0,0,23,0,-7,0,0,48};
	struct Q3Struct int_result[8] = {0};
	int expected[8] = {0,0,23,0,-7,0,0,48};
	int actual[8] = {0};
	efficient(input,int_result,n);
	reconstruct(actual, 8, int_result, 3);

	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i], actual[i]);
	}
}

void TestQ3_combined2(CuTest *tc) {
	int n=8;
	int input[]={22,21,23,0,-7,0,0,48};
	struct Q3Struct int_result[8] = {0};
	int expected[8] = {22,21,23,0,-7,0,0,48};
	int actual[8] = {0};
	efficient(input,int_result,n);
	reconstruct(actual, 8, int_result, 5);

	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i], actual[i]);
	}
}
    

//===========================================================
//=================Question 4================================   
void TestQ4_BubbleSort_1(CuTest *tc) 
{
	int n=6;
	struct Q4Struct input[]={{10, 'c'}, {2, 'B'}, {-5, 'k'}, {12, 'z'}, {77, 'a'}, {-42, '?'}};	
	struct Q4Struct expected[]={{-42, '?'}, {-5, 'k'}, {2, 'B'}, {10, 'c'}, {12, 'z'}, {77, 'a'}};		
	
	sortDatabyBubble(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}

void TestQ4_BubbleSort_2(CuTest *tc) 
{
	int n=8;
	struct Q4Struct input[]={{-23, '='}, {78, ' '}, {11, 'Y'}, {-2, '0'}, {41, '+'}, {0, 'm'}, {55, 'T'}, {-9, 'o'}};	
	struct Q4Struct expected[]={{-23, '='}, {-9, 'o'}, {-2, '0'}, {0, 'm'}, {11, 'Y'}, {41, '+'}, {55, 'T'}, {78, ' '}};		
	
	sortDatabyBubble(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}

void TestQ4_BubbleSort_3(CuTest *tc) 
{
	int n=8;
	struct Q4Struct input[]={{-2233, '='}, {784, ' '}, {1121, 'Y'}, {-442, '0'}, {0, '+'}, {0, 'm'}, {3, 'T'}, {-19, 'o'}};	
	struct Q4Struct expected[]={{-2233, '='}, {-442, '0'}, {-19, 'o'}, {0, '+'}, {0, 'm'}, {3, 'T'}, {784, ' '}, {1121, 'Y'}};		
	
	sortDatabyBubble(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}

void TestQ4_SelectionSort_1(CuTest *tc) 
{
	int n=6;
	struct Q4Struct input[]={{10, 'c'}, {2, 'B'}, {-5, 'k'}, {12, 'z'}, {77, 'a'}, {-42, '?'}};	
	struct Q4Struct expected[]={{-42, '?'}, {-5, 'k'}, {2, 'B'}, {10, 'c'}, {12, 'z'}, {77, 'a'}};		
	
	sortDatabySelection(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}

void TestQ4_SelectionSort_2(CuTest *tc) 
{
	int n=8;
	struct Q4Struct input[]={{-23, '='}, {78, ' '}, {11, 'Y'}, {-2, '0'}, {41, '+'}, {0, 'm'}, {55, 'T'}, {-9, 'o'}};	
	struct Q4Struct expected[]={{-23, '='}, {-9, 'o'}, {-2, '0'}, {0, 'm'}, {11, 'Y'}, {41, '+'}, {55, 'T'}, {78, ' '}};			
	
	sortDatabySelection(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}

void TestQ4_SelectionSort_3(CuTest *tc) 
{
	int n=8;
	struct Q4Struct input[]={{-444, '='}, {222, ' '}, {0, 'Y'}, {0, '0'}, {3123, '+'}, {44, 'm'}, {545, 'T'}, {-9, 'o'}};	
	struct Q4Struct expected[]={{-444, '='}, {-9, 'o'}, {0, 'Y'}, {0, '0'}, {44, 'm'}, {222, ' '}, {545, 'T'}, {3123, '+'}};		
	
	sortDatabySelection(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}

void TestQ4_SelectionSort_4(CuTest *tc) 
{
	int n=8;
	struct Q4Struct input[]={{-444, '='}, {222, ' '}, {0, 'Y'}, {0, '0'}, {3123, '+'}, {22, 'm'}, {545, 'T'}, {-9, 'o'}};	
	struct Q4Struct expected[]={{-444, '='}, {-9, 'o'}, {0, 'Y'}, {0, '0'}, {22, 'm'}, {222, ' '}, {545, 'T'}, {3123, '+'}};		
	
	sortDatabySelection(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}





CuSuite* Lab2GetSuite() {

	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, TestQ1_add);
	SUITE_ADD_TEST(suite, TestQ1_add2);
	SUITE_ADD_TEST(suite, TestQ1_scalar_prod);
	SUITE_ADD_TEST(suite, TestQ1_scalar_prod2);
	SUITE_ADD_TEST(suite, TestQ1_norm);
	SUITE_ADD_TEST(suite, TestQ1_norm2);

	SUITE_ADD_TEST(suite, TestQ2);

	SUITE_ADD_TEST(suite, TestQ3_1);
	SUITE_ADD_TEST(suite, TestQ3_2);
	SUITE_ADD_TEST(suite, TestQ3_3);
	SUITE_ADD_TEST(suite, TestQ3_zeros);
	SUITE_ADD_TEST(suite, TestQ3_combined);
	SUITE_ADD_TEST(suite, TestQ3_combined2);

	SUITE_ADD_TEST(suite, TestQ4_BubbleSort_1);
	SUITE_ADD_TEST(suite, TestQ4_BubbleSort_2);
	SUITE_ADD_TEST(suite, TestQ4_BubbleSort_3);
	SUITE_ADD_TEST(suite, TestQ4_SelectionSort_1);
	SUITE_ADD_TEST(suite, TestQ4_SelectionSort_2);
	SUITE_ADD_TEST(suite, TestQ4_SelectionSort_3);
	SUITE_ADD_TEST(suite, TestQ4_SelectionSort_4);


	return suite;
}
    
