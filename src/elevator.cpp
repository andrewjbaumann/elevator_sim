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
#include "customer.hpp"
#include "elevator.hpp"
using namespace std;

//constructor 
Elevator::Elevator(int call, int m)
{
	callsign = call;
	level = 1;
	direction = 1;
	total_weight = 0;
	max = m;
}
//deconstructor
Elevator::~Elevator()
{
	passengers.clear();
	
}

int Elevator::return_level()
{
	return level;
}

char Elevator::return_callsign()
{
	return callsign;
}

bool Elevator::return_direction()
{
	return direction;
}

int Elevator::return_weight()
{
	return total_weight;
}
//changes floor
int Elevator::change_level(int l)
{
	level = l;
	return level;
}
//changes direction
bool Elevator::change_direction(bool going_up)
{
	direction = going_up;
	return going_up;
}
//changes weight
bool Elevator::change_weight(bool add, int weight)
{	
	if(add)
	{
		total_weight += weight;
		if(total_weight > max)
		{
			total_weight -= weight;
			return 0;
		}
	}
	else
		total_weight -= weight;

	return 1;
}

//adds a passenger to the elevator
bool Elevator::add_passenger(Customer * human)
{
	const int dest = human->return_dest();
	const int weight = human->return_weight();
		if(!change_weight(1,weight))
			return 0;
		if(direction)
		{
			if(dest > level)
			{
				passengers.push_back(human);
				return 1;
			}
		}	
		else
		{
			if(dest < level)
			{
				passengers.push_back(human);
				return 1;
			}
		}
	return 0;
}

//true if passengers are onboard
bool Elevator::return_passengers()
{
	if(passengers.size() == 0)
		return 0;
	else 
		return 1;

}
//removes passengers; not used only in testing
bool Elevator::kill_passengers()
{
	list<Customer*>::iterator killer;
	if(passengers.size() == 0)
	{ 	
		return 0;
	}
	else
	{
		for(killer=passengers.begin(); killer != passengers.end(); killer++)
		{
			if(level == (*killer)->return_dest())
			{
				int remove = (*killer)->return_weight();
				change_weight(0,remove);
				passengers.erase(killer);
				killer--;
			}
		}
	return 1;
	}
return 0;
}



