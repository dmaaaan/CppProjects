/*
 * main.cpp
 *
 *  Created on: 27 cze 2019
 *      Author: Denis
 */
#include <cstdlib>											//all three needed for usage of srand
#include <iostream>
#include <fstream>											//usage of extern files
#include <ctime>

#include "locale.h" 										//for setlocale
#include "COther.h"

using namespace std;

int main()
{

	setlocale(LC_ALL, "polish");
	srand(time(0));

	//CGraph objMain;
	COther obj1;


	obj1.enterBegin();

	obj1.printAdjList();
	obj1.calcDistances();
	obj1.printMST();

	return 0;
}
