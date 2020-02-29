#ifndef NODE_H
#define NODE_H


#include<iostream>
#include<string>
#include"Date.h"
#include"Time.h"
#include"Vector.h"
using namespace std;


class node
{
	public:

		node* next;													//pointer to next node
		string destination;											//name of destination
		Vector<int> cost;											//cost of ticket
		int Stay_charges;											//hotel rent
		Vector<Date> date;											//date of flight
		Vector<Time> time_departure;											// time of departure of flight
		Vector<Time> time_arrival;										//time of arrival of the flight
		Vector<string> air_line;									// name of airline

		node();

};


node::node()
{
	next = NULL;
	Stay_charges = 0;
	destination = "\0";
}


#endif