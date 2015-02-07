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
#include <stdlib.h>
#include <time.h>
#include "customer.hpp"
using namespace std;

Customer::Customer(int w, int d, int l)
{
	weight = w;
	destination = d;
	level = l;
	minutes_waited=0;
}

Customer::~Customer()
{
}

int Customer::return_weight()
{
	return weight;
}

int Customer::return_dest()
{
	return destination;
}

int Customer::return_level()
{
	return level;
}

int Customer::return_minutes()
{
	return minutes_waited;
}

void Customer::increment_minutes()
{
	minutes_waited++;
}