 
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
#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include <iostream>
#include <list>
using namespace std;

class Customer {
private:
	int weight; 
	int level;
	int destination;
	int minutes_waited;
public:
	Customer(int w, int d, int l);
	~Customer();
	int return_weight();
	int return_level();
	int return_dest();
	int return_minutes();
	void increment_minutes();
};
#endif