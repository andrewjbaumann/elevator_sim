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
#ifndef BUILDING_HPP
#define BUILDING_HPP
#include <iostream>
#include <list>
#include <fstream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>     
#include "elevator.hpp"
#include "customer.hpp"
using namespace std;

class Building 
{
private:
	int elevators; // number of elevators in the bank
	int levels; //numer of floors
	int min_weightc; //min weight per human
	int max_weightc; //max weight per human
	int weight_limit; //weight limit for an elevator
	double per_min; //number of humans generated on all floors per minute
	list<Elevator*> total; //the elevators in operation
	list<Customer*> in_building; //the people in the building not on an elevator
	double total_min_waited; //total minutes waited
	double people_ever_waited; // people who waited
	double first_avg; //average weight time
public:
	Building(fstream & file);
	~Building();

	void reader(fstream & file); //reads the text document
	void create_elevators(); //fills the list with elevators 
	int generate_weight(); //generates a customer weight
	int generate_level(); //generates a customer dest level
	void create_customers(); //creates the customers
	void sort_humans(); //sorts humans in_building
	void eight_hours(); //the eight hour run time
	void every_minute(); //a checker for each minute
	bool floor_check(list<Elevator*>::iterator elevator); //determines whether an elevator stops
	//or continues for each floor it passes 
	//returns a yes if passenger does not exceed weight limit, returns no otherwise
	bool weight_check(list<Elevator*>::iterator elev, int weight); //checks weight; not used
	void clean_up(); //adds the passengers who never got on the elevator's wait time to the max
};
#endif
