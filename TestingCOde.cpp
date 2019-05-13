// TestingCOde.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BigNumbers.h"

int main()
{
    std::cout << "Hello World!\n"; 
	BigNumbers test(100);
	BigNumbers test2(10);
	BigNumbers test3(-99);
	BigNumbers test4(-1090);
	BigNumbers temp;

	temp = (test %test2);
	temp.printNumber();


	/*
	temp = (test+test2);	
	temp.printNumber();

	temp = (test3 + test4);
	temp.printNumber();

	temp = (test + test3);
	temp.printNumber();

	temp = (test4 + test3);
	temp.printNumber();

	std::cout << "Addition Tests Complete\n\n" << std::endl;
	temp = (test - test2);
	temp.printNumber();

	temp = (test - test3);
	temp.printNumber();

	temp = (test4 - test);
	temp.printNumber();

	temp = (test3 - test4);
	temp.printNumber();


	*/

	/*
	temp = (test - test2);
	temp.printNumber();
	*/
}
