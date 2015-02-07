/******************************************************************************
Title : customer.hpp
Author : Andrew Baumann, Tony Zheng
Created on : May 2014
Description : An elevator program that simulates a full 8 hour shift of 
elevator operation in some building, and telling the user how many minutes
the average person waited.
Bugs : Does not follow assignment in running twice, the second time with 
one less elevator
The weight_check function is bugged. The program works as desired without it,
which is why it is commented out. 
Build With : g++ customer.cpp elevator.cpp building.cpp main.cpp -o run.exe
Special Thanks : David Guy Brizan, Danny Wu
******************************************************************************/
#include <iostream>
#include <list>
#include <fstream>
#include <stdio.h>      
#include <stdlib.h>     
#include <ctime>    
#include <time.h>
#include "elevator.hpp"
#include "customer.hpp"
#include "building.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	fstream file(argv[1]);
	fstream read(argv[1]);
	Building * DRAGON = new Building(file);
	delete DRAGON;
return 0;
}
