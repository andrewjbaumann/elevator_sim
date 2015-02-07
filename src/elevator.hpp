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
#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP
#include <iostream>
#include <list>
#include "customer.hpp"
using namespace std;

class Elevator 
{
private:
	int callsign;
	int level;
	bool direction;
	int total_weight;
	int max;

public:
	Elevator(int callsign, int max);
	~Elevator();

	list <Customer*> passengers;
	int return_level();
	bool return_direction();
	char return_callsign();
	int return_weight();
	int change_level(int l);
	bool change_direction(bool going_up);
	bool change_weight(bool add, int weight);
	bool add_passenger(Customer * human);
	bool return_passengers();
	bool kill_passengers();

};
#endif