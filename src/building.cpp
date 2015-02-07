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
#include <string>
#include "elevator.hpp"
#include "customer.hpp"
#include "building.hpp"

using namespace std;

Building::Building(fstream & file)
{
	srand (time(NULL));
	reader(file);
	create_elevators();
	create_customers();
	eight_hours();
	first_avg = total_min_waited / people_ever_waited;
	cout << total_min_waited << "-" << people_ever_waited << endl;
	cout << first_avg << endl;
}

Building::~Building()
{
	in_building.clear();
	total.clear();
}

void Building::reader(fstream & file)
{
	string reading;
	char elev_num[20];
	char rlevels[20];
	char wlimit[20];
	char wmin[20];
	char wmax[20];
	char customers[20];
	if(file.is_open())
	{
		while(file.good())
		{
			getline(file,reading);
			for(int i=0; i<reading.size(); i++)
			{
				if(reading[0]=='#')
					getline(file,reading);
				else if(reading[0] == 'e')
					for(int i=12;i <= reading.size(); i++)
						elev_num[i-12] = reading[i];
				else if(reading[0] == 'f')
					for(int i=9; i <= reading.size(); i++)
						rlevels[i-9] = reading[i];
				else if(reading[0] == 'w')		
					for(int i=15;i<= reading.size(); i++)
					wlimit[i-15] = reading[i];
				else if(reading[1] == 'i')		
					for(int i=13;i<= reading.size(); i++)
						wmin[i-13] = reading[i];
				else if(reading[1] == 'a')
					for(int i=13;i<= reading.size(); i++)
						wmax[i-13] = reading[i];
				else if(reading[0] == 'c')		
					for(int i=11;i<= reading.size(); i++)
						customers[i-11] = reading[i];	
			}
		}
	}
	elevators = atoi(elev_num); // number of elevators in the bank
	levels = atoi(rlevels); //numer of floors
	min_weightc = atoi(wmin); //min weight per human
	max_weightc = atoi(wmax); //max weight per human
	weight_limit = atoi(wlimit); //weight limit for an elevator
	per_min = atof(customers); //number of humans generated on all floors per minute	
	file.close();
}

void Building::create_elevators()
{
	for(int i=0; i<elevators; i++)
	{
		Elevator * bay;
		bay = new Elevator(i, weight_limit);
		total.push_back(bay);
		delete bay;
	}
}

int Building::generate_weight()
{
	int temp = rand() % max_weightc + min_weightc;
	return temp;
}

int Building::generate_level()
{
	int temp = rand() % levels + 1;
	return temp;
}

void Building::create_customers()
{
	for(int i=1; i<levels; i++)
	{
		Customer * human;
		int weight = generate_weight();
		int dest= 0;
		do { //prevents a customer from having the same current floor and destination
		dest = generate_level();
		} 	while (i == dest);
		human = new Customer(weight, dest, i);
		in_building.push_back(human);
	}
	sort_humans();
}

void Building::sort_humans()
{
	list<Customer*>::iterator outter;
	list<Customer*>::iterator inner;
	int size = in_building.size();

	for(int i=0; i!=size; i++)
		for(outter=in_building.begin(); outter!=in_building.end(); outter++)
			for(inner=outter; inner!= in_building.end(); inner++)
				if((*outter)->return_level() > (*inner)->return_level())
				    in_building.splice(outter,in_building,inner);
}

void Building::eight_hours()
{
	int minutes_past=0;
	const float human_creator = per_min;	//480 minutes = 8 hours
	while(minutes_past<480)
	{
		every_minute(); //picks up and kills passengers
		minutes_past++; //increases by 1 minute
		per_min += human_creator; //increases "number of customers generated per minute"
		//puts a person at every floor when per_minute calculation is above 1
		if(per_min >= 1)
		{
			create_customers();
			per_min = 0;
			people_ever_waited += levels;
		}	
	for(list<Customer*>::iterator killer = in_building.begin(); killer != in_building.end(); killer++)
		(*killer)->increment_minutes();
	}
clean_up();
}

void Building::every_minute()
{
	list<Elevator*>::iterator i;
	int ten=0;
	//we address every elevator in the minute, starting with elevator 0
	for(i=total.begin(); i!=total.end(); i++)
	{
		if((*i)->return_direction()) //if elevator is going up
		{
			//checks every floor and only increments if no stop is made after 10 floors are passed
			while((!floor_check(i)) && (ten<10)) 
			{ 
				if((*i)->return_level()==levels)
				{
					ten=10; //we stop when we hit the top and change direction
					(*i)->change_direction(0);
				}
				else
				{
					(*i)->change_level((*i)->return_level()+1);
					ten++;
				}
			}
		}
		else //else the elevator is going down
		{
			while((!floor_check(i)) && (ten<10))
			{
				if((*i)->return_level()==0)
				{
					(*i)->change_direction(1);
					ten=10;
				}
				else
				{
					(*i)->change_level((*i)->return_level()-1);
					ten++;
				}
			}
		}
	}
}

//floor check returns yes if any passengers were killed or joined the elevator
bool Building::floor_check(list<Elevator*>::iterator elevator)
{
	const int level_now = (*elevator)->return_level();
	const bool direction = (*elevator)->return_direction();
	int increment = 1;
	bool stopped = 0;
	/*passengers getting off the elevator ***killed***
	if the passenger gets off, then as far as the elevator is concerned,
	they cease to exist. so, arguing semantics, a passenger getting off
	at their stop is no different to them dying in terms of the elevator*/
	if((*elevator)->passengers.size() > 0)
	{
		for(list<Customer*>::iterator killer = (*elevator)->passengers.begin(); killer != (*elevator)->passengers.end(); killer++)
		{
			int w = (*killer)->return_weight();
			if((*killer)->return_dest() == level_now)
			{	
				//(*elevator)->change_weight(0, w);
  				(*elevator)->passengers.erase(killer);
				killer--;
				stopped=1;
			}
		}
	}
	//passengers getting on the elevator
	for(list<Customer*>::iterator killer = in_building.begin(); killer != in_building.end(); killer++)
	{
		int w = (*killer)->return_weight();
		if((direction) && ((*killer)->return_level() == level_now))
		{
			if(((*killer)->return_dest() > level_now) /*&& (weight_check((elevator), w))*/)
			{
				(*elevator)->passengers.push_back(*killer);
				total_min_waited += (*killer)->return_minutes();
				in_building.erase(killer);
				killer--;
				stopped=1;
			}
		}
		else if (((*killer)->return_level() == level_now)/* && (weight_check((elevator), w))*/)
		{
			if((*killer)->return_dest() < level_now)
			{	
				(*elevator)->passengers.push_back(*killer);
				total_min_waited += (*killer)->return_minutes();
				in_building.erase(killer);
				killer--;
				stopped=1;
			}
		}		
	}		
	return stopped;
}

//checks weight; not used
bool Building::weight_check(list<Elevator*>::iterator elev, int weight)
{
	if((*elev)->change_weight(1,weight))
		return 1;
	else
		return 0;
}

//adds the wait time of anyone who did not get on the elevator after time expired
void Building::clean_up()
{
	for(list<Customer*>::iterator cust = in_building.begin(); cust != in_building.end(); cust++)
		total_min_waited += (*cust)->return_minutes();
}







