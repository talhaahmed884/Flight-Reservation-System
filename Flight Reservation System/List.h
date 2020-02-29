#ifndef LIST_H
#define LIST_H


#include<iostream>
#include<cstring>
#include<string>
#include"Node.h"


class List
{

	public:
	
		node* head;									//list that contains information about all flights from on starting point
		node* tail;
		int size;						//Shows the number of nodes in the List

		List();
		void insert_end(node*);
		bool isEmpty();					//Checks if the list is empty
		bool duplicate(node*);			//Checks if the duplicate enitity is available
		int getSize();					//Return Size of the list
		void clear();					//Clear the whole list
		node* pop();					//Delete the last element in the list
};


List::List()
{
	head = NULL;
	tail = NULL;
	size = 0;
}


void List::insert_end(node* NEW)
{
	if (head == NULL)
	{
		node* temp = new node();
		temp->air_line.insert(NEW->air_line[0]);
		temp->cost.insert(NEW->cost[0]);
		temp->date.insert(NEW->date[0]);
		temp->destination = NEW->destination;
		temp->next = NULL;
		temp->Stay_charges = NEW->Stay_charges;
		temp->time_arrival.insert(NEW->time_arrival[0]);
		temp->time_departure.insert(NEW->time_departure[0]);
		head = temp;
		tail = head;
		//tail->next = NULL;
		size++;
	}
	else
	{
		node* temp = new node();
		temp->air_line.insert(NEW->air_line[0]);
		temp->cost.insert(NEW->cost[0]);
		temp->date.insert(NEW->date[0]);
		temp->destination = NEW->destination;
		temp->next = NULL;
		temp->Stay_charges = NEW->Stay_charges;
		temp->time_arrival.insert(NEW->time_arrival[0]);
		temp->time_departure.insert(NEW->time_departure[0]);
		tail->next = temp;
		tail = tail->next;
		//tail->next = NULL;
		size++;
	}
	return;
}


bool List::isEmpty()					//Checks if the list is empty
{
	if (head == NULL && size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool List::duplicate(node* temp)			//Checks if the duplicate enitity is available
{
	node* temp_one = head;
	while (temp_one != NULL)
	{
		int index = temp_one->date.Size();
		for (int a = 0; a < index; a++)
		{
			if (temp_one->destination == temp->destination && temp_one->air_line[a] == temp->air_line[0] && temp_one->cost[a] == temp->cost[0] && temp_one->date[a].get_Date() == temp->date[0].get_Date() && temp_one->Stay_charges == temp->Stay_charges && temp_one->time_arrival[a].get_Time() == temp->time_arrival[0].get_Time() && temp_one->time_departure[a].get_Time() == temp->time_departure[0].get_Time())
			{
				return true;
			}
		}
		temp_one = temp_one->next;
	}
	return false;
}


int List::getSize()					//Return Size of the list
{
	return size;
}


void List::clear()				//Clear the whole list
{
	node* temp = head;
	while (temp != NULL)
	{
		node* temp_one = temp;
		temp = temp->next;
		delete temp_one;
	}
	size = 0;
	head = NULL;
	tail = NULL;
	return;
}


node* List::pop()					//Delete the last element in the list
{
	if (head != NULL)
	{
		node* temp = head;
		while (temp->next != tail)
		{
			temp = temp->next;
			if (temp == NULL)
			{
				break;
			}
		}
		node* temp_one = tail;
		tail = temp;
		if (tail != NULL)
		{
			tail->next = NULL;
			temp = temp->next;
		}
		else
		{
			head = NULL;
			tail = NULL;
		}
		size--;
		delete temp;
		return temp_one;
	}
	return NULL;
}


#endif