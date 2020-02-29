#ifndef GRAPH_H
#define GRAPH_H


#include"List.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


class Graph
{
	protected:
	
		List* source;				//Stores the whole graph
		Vector<string> source_name;				//Contains all the sources of the
		int Total_sources;					//Contains the total size of the sources
		int max_size;					//Maximum sources that can be added into the graph

		int to_int(string);				//Used to convert string to integer
		node* createNode(string, int, int, Date, Time&, Time&, string);				//Creates a new Node for storage
		void traverseScenerioOne(node*, List*, string, Date&, string);							//Helping function for Scenerio One
		bool traverseScenerioOne(node*, string, Date&, string, List*);			//Helping function for Scenerio One
		void traverseScenerioOne(node*, List*, string, Date&, string, Time&);							//Helping function for Scenerio One
		void sortCost(List*);									//Sort the list on the basis of cost
		void sortCost(List*, List*, Vector<string>*, Vector<string>*);									//Sort the list on the basis of cost
		void traverseScenerioTwo(node*, List*, string, Date&);							//Helping function for Scenerio Two
		bool traverseScenerioTwo(node*, string, Date&, List*);			//Helping function for Scenerio Two
		void traverseScenerioTwo(node*, List*, string, Date&, Time&);							//Helping function for Scenerio two
		void sortTime(List*);												//Helping function for sorting the data with  respect to time difference
		void sortTime(List*, List*, Vector<string>*, Vector<string>*);												//Helping function for sorting the data with respect to time difference

	public:

		Graph();				//Default Constructor
		Graph(int,string,string,int,int,Date&,Time&,Time&,string);			//Parameterized Constructor
		void setmaxSize(int);						//It intially sets the size of the list
		void insertEdge(string,string,int,int,Date&,Time&,Time&,string);						//Insert edges and create vertices
		void createGraph(string,string);				//It reads data from the file and create the graph accordingly
		void display();					//It is used to display the whole Graph
		void scenerioOne(string,string,Date&,string, List*, List*, List*, Vector<string>*, Vector<string>*);				//The function handeling all the requests regarding Scenerio one
		void scenerioTwo(string,string,Date&, List*, List*, List*, Vector<string>*, Vector<string>*);				//The function handeling all the requests regarding Scenerio two
		void Scenerio_5(List*, Vector<string>&, string, string, Date);							//The function handeling all the requests regarding Scenerio five
		void scenerioFour(string,string,Date& , string, int, List*, List*, Vector<string>*, Vector<string>*);				//The function handeling all the requests regarding Scenerio four

};



Graph::Graph()
{
	source = NULL;
	Total_sources = 0;
	max_size = 0;
}


Graph::Graph(int maxSize,string Source,string Destination, int Cost, int stayCharges, Date& date, Time& time_depart, Time& time_arriv, string airLine)
{
	source = new List[maxSize];
	max_size = maxSize;
	source_name.insert(Source);
	node* temp = createNode(Destination,Cost,stayCharges,date,time_depart,time_arriv,airLine);
	source[0].insert_end(temp);
	Total_sources = 1;
}


node* Graph::createNode(string Destination, int Cost, int stayCharges, Date Date, Time& Time_depart, Time& time_arriv, string airLine)				//Creates a new Node for storage
{
	node* temp = new node();
	temp->destination = Destination;
	temp->cost.insert(Cost);
	temp->Stay_charges = stayCharges;
	temp->date.insert(Date);
	temp->time_departure.insert(Time_depart);
	temp->time_arrival.insert(time_arriv);
	temp->air_line.insert(airLine);
	temp->next = NULL;
	return temp;
}


void Graph::setmaxSize(int maxSize)						//It intially sets the size of the list
{
	source = new List[maxSize];
	max_size = maxSize;
	return;
}


void Graph::createGraph(string hotelCharges, string flights)				//It reads data from the file and create the graph accordingly
{
	setmaxSize(1);						//Set the intial number of nodes in the graph
	fstream readFile_one;
	readFile_one.open(hotelCharges.c_str(), ios::in);				//Reading the Hotel Staying charges
	Vector<string> hotel_cities;
	Vector<int> hotel_citiesCost;
	while (!readFile_one.eof())
	{
		string city,cost;
		readFile_one >> city >> cost;
		hotel_cities.insert(city);
		int temp_cost = to_int(cost);
		hotel_citiesCost.insert(temp_cost);
	}
	readFile_one.close();
	readFile_one.open(flights.c_str(), ios::in);				//Reading the flight schedule from the file
	while (!readFile_one.eof())
	{
		string source, destination, date, time1, time2, cost, airLine;
		readFile_one >> source >> destination >> date >> time1 >> time2 >> cost >> airLine;
		Date date1; date1.set_Date(date);
		Time time3; time3.set_Time(time1);
		Time time4; time4.set_Time(time2);
		int tempCost = to_int(cost);
		int index = hotel_cities.find(destination);
		int stayCharges = 0;
		if (index != -1)
		{
			stayCharges = hotel_citiesCost[hotel_cities.find(destination)];
		}
		insertEdge(source, destination, tempCost, stayCharges, date1, time3, time4, airLine);
	}
	readFile_one.close();
	return;
}


void Graph::insertEdge(string Source, string Destination, int Cost, int stayCharges, Date& Date, Time& Time_depart, Time& time_arrival, string airLine)						//Insert edges and create vertices
{
	if (Total_sources  >= max_size)
	{
		int temp_max = max_size;
		max_size = Total_sources+1;
		List *temp_list = new List[temp_max];
		for (int a = 0; a < temp_max; a++)
		{
			temp_list[a] = source[a];
		}
		delete[] source;
		source = new List[max_size];
		for (int a = 0; a < temp_max; a++)
		{
			source[a] = temp_list[a];
		}
		delete[] temp_list;
	}
	for (int a = 0; a < max_size; a++)
	{
		if (!source[a].isEmpty())
		{
			node* temp_one = source[a].head;
			while (temp_one != NULL)
			{
				if (source_name[a] == Source && temp_one->destination == Destination)
				{
					temp_one->cost.insert(Cost);
					temp_one->date.insert(Date);
					temp_one->time_departure.insert(Time_depart);
					temp_one->time_arrival.insert(time_arrival);
					temp_one->air_line.insert(airLine);
					return;
				}
				temp_one = temp_one->next;
			}
			if (source_name[a] == Source)
			{
				node* temp = createNode(Destination, Cost, stayCharges, Date, Time_depart, time_arrival, airLine);
				source[a].insert_end(temp);
				return;
			}
		}
		else
		{
			source_name.insert(Source);
			node* temp = createNode(Destination, Cost, stayCharges, Date, Time_depart, time_arrival, airLine);
			source[a].insert_end(temp);
			Total_sources++;
			return;
		}
	}
}


void Graph::display()					//It is used to display the whole Graph
{
	cout << "Sources: " << Total_sources << endl;
	cout << "Max Size: " << max_size << endl;
	for (int a = 0; a < max_size; a++)
	{
		if (!source[a].isEmpty())
		{
			node* temp = source[a].head;
			while (temp != NULL)
			{
				int vect_size = temp->date.Size();
				for (int b = 0; b < vect_size; b++)
				{
					cout << source_name[a] << " ";
					cout << temp->destination << " ";
					cout << temp->date[b].get_Date() << " ";
					cout << temp->time_departure[b].get_Time() << " ";
					cout << temp->time_arrival[b].get_Time() << " ";
					cout << temp->cost[b] << " ";
					cout << temp->air_line[b] << " ";
					cout << temp->Stay_charges << endl;
				}
				temp = temp->next;
			}
		}
	}
	return;
}


int Graph::to_int(string word)				//Used to convert string to integer
{
	stringstream str(word);	int temp;	str >> temp;	return temp;
}


void Graph::scenerioOne(string Source, string Destination, Date& date, string airLine, List* directFlights, List* indirectFlights, List* indirectFlightsHead, Vector<string>* indirectflightSource, Vector<string>* indirectFlightsHeadSource)		//The function handeling all the requests regarding Scenerio one
{
	int index = source_name.find(Source);
	node* temp = source[index].head;
	traverseScenerioOne(temp, directFlights, Destination, date, airLine);				//Recursive function that move around the graph and find any direct links available

	Vector<string> visitedLocations;

	while (temp != NULL)
	{
		if (temp->destination != Destination)
		{
			if (visitedLocations.find(temp->destination) == -1)
			{
				visitedLocations.insert(temp->destination);
				List* tempList = new List();
				bool flightCheck = traverseScenerioOne(temp, temp->destination, date, airLine, tempList);
				if (flightCheck)
				{
					node* temp_two = tempList->head;
					while (temp_two != NULL)
					{
						int index_one = source_name.find(temp->destination);
						if (index_one != -1)
						{
							node* temp_one = source[index_one].head;
							int temp_size = indirectFlights->getSize();
							traverseScenerioOne(temp_one, indirectFlights, Destination, date, airLine, temp_two->time_arrival[0]);
							if (temp_size < indirectFlights->getSize())
							{
								while (temp_size < indirectFlights->getSize())
								{
									indirectFlightsHeadSource->insert(source_name[index]);
									indirectflightSource->insert(source_name[index_one]);
									indirectFlightsHead->insert_end(temp_two);
									temp_size++;
								}
							}
						}
						temp_two = temp_two->next;
					}
				}
			}
		}
		temp = temp->next;
	}

	sortCost(directFlights);					//Sort the direct flights on the basis of cost

	if (directFlights->head == NULL)
	{
		cout << "No Direct Flights available.\n";
	}
	else
	{
		node* temp = directFlights->head;
		cout << "Direct Flights available.\n\n";
		for (int a = 0; temp != NULL; a++)
		{
			cout << "Flight" << a + 1 << endl;
			cout << Source << " " << Destination << " " << date.get_Date() << " " << temp->time_departure[0].get_Time() << " " << temp->time_arrival[0].get_Time() << " " << temp->cost[0] << " " << airLine << endl << endl;
			temp = temp->next;
		}
	}

	if (indirectFlights->head == NULL || indirectFlightsHead->head == NULL)
	{
		indirectFlights->clear();
		indirectflightSource->Clear();
		indirectFlightsHead->clear();
		indirectFlightsHeadSource->Clear();
	}

	sortCost(indirectFlights, indirectFlightsHead, indirectflightSource, indirectFlightsHeadSource);


	if (indirectFlights->head == NULL)
	{
		cout << "\nNo Connected Flights available.\n";
	}
	else
	{

		node* temp = indirectFlights->head;
		node* temp_one = indirectFlightsHead->head;
		cout << "\nConnected Flights available.\n";
		for (int a = 0; temp != NULL && temp_one!=NULL ; a++)
		{

			cout << "Flight " << a + 1 << endl;
			if (indirectFlightsHeadSource->Size() > a)
			{
				cout << indirectFlightsHeadSource[0][a] << " ";
			}
			cout<< temp_one->destination << " " << date.get_Date() << " " << temp_one->time_departure[0].get_Time() << " " << temp_one->time_arrival[0].get_Time() << " " << temp_one->cost[0] << " " << airLine << " " << temp_one->Stay_charges << endl;
			if (indirectflightSource->Size() > a)
			{
				cout << indirectflightSource[0][a] << " ";
			}
			cout<< temp->destination << " " << date.get_Date() << " " << temp->time_departure[0].get_Time() << " " << temp->time_arrival[0].get_Time() << " " << temp->cost[0] << " " << airLine << " " << temp->Stay_charges << endl;
			temp = temp->next;
			temp_one = temp_one->next;
		}
	}
	return;
}


void Graph::traverseScenerioOne(node* temp, List* list, string Destination, Date& date, string airLine)							//Helping function for Scenerio One
{
	if (temp == NULL)
	{
		return;
	}
	else
	{
		int index = temp->air_line.Size();
		for (int a = 0; a < index; a++)
		{
			if (temp->time_departure[a].get_Hours() >= 0 && temp->time_arrival[a].get_Hours() < 24)
			{
				if (temp->destination == Destination && temp->date[a].get_Date() == date.get_Date() && airLine == temp->air_line[a])
				{
					node* tempNode = createNode(Destination, temp->cost[a], temp->Stay_charges, date, temp->time_departure[a], temp->time_arrival[a], airLine);
					list->insert_end(tempNode);
				}
			}
		}
		traverseScenerioOne(temp->next, list, Destination, date, airLine);
		return;
	}
}


bool Graph::traverseScenerioOne(node* temp, string Destination, Date& date, string airLine, List* list)				//Helping function for Scenerio One
{
	int index = temp->date.Size();
	for (int a = 0; a < index; a++)
	{
		if (temp->time_departure[a].get_Hours() >= 0 && temp->time_arrival[a].get_Hours() < 24)
		{
			if (temp->destination == Destination && temp->date[a].get_Date() == date.get_Date() && temp->air_line[a] == airLine)
			{
				node* tempNode = createNode(Destination, temp->cost[a], temp->Stay_charges, date, temp->time_departure[a], temp->time_arrival[a], airLine);
				list->insert_end(tempNode);
			}
		}
	}
	if (list->isEmpty())
	{
		return false;
	}
	else
	{
		return true;
	}
}


void Graph::sortCost(List* list)									//Sort the list on the basis of cost
{
	node* temp = list->head;
	if (temp != NULL)
	{
		while (temp->next != NULL)
		{
			node* temp_one = temp->next;
			while (temp_one != NULL)
			{
				if (temp->cost[0] > temp_one->cost[0])
				{
					string tempDest = temp->destination;
					int tempCost = temp->cost[0];
					Time temptimeDepart = temp->time_departure[0];
					Time temptimeArr = temp->time_arrival[0];
					string tempAir = temp->air_line[0];
					int tempStayCharge = temp->Stay_charges;
					Date tempDate = temp->date[0];

					temp->destination = temp_one->destination;
					temp->air_line[0] = temp_one->air_line[0];
					temp->cost[0] = temp_one->cost[0];
					temp->date[0] = temp_one->date[0];
					temp->Stay_charges = temp_one->Stay_charges;
					temp->time_departure[0] = temp_one->time_departure[0];
					temp->time_arrival[0] = temp_one->time_arrival[0];

					temp_one->destination = tempDest;
					temp_one->air_line[0] = tempAir;
					temp_one->cost[0] = tempCost;
					temp_one->date[0] = tempDate;
					temp_one->Stay_charges = tempStayCharge;
					temp_one->time_departure[0] = temptimeDepart;
					temp_one->time_arrival[0] = temptimeArr;
				}
				temp_one = temp_one->next;
			}
			temp = temp->next;
		}
	}
}


void Graph::traverseScenerioOne(node* temp, List* list, string Destination, Date& date, string airLine, Time& time)							//Helping function for Scenerio One
{
	if (temp == NULL)
	{
		return;
	}
	else
	{
		int index = temp->air_line.Size();
		for (int a = 0; a < index; a++)
		{
			if (temp->time_departure[a].get_Hours() >= 0 && temp->time_arrival[a].get_Hours() < 24)
			{
				if (temp->destination == Destination && temp->date[a].get_Date() == date.get_Date() && airLine == temp->air_line[a] && temp->time_departure[a].get_Hours() > time.get_Hours())
				{
					node* tempNode = createNode(Destination, temp->cost[a], temp->Stay_charges, date, temp->time_departure[a], temp->time_arrival[a], airLine);
					list->insert_end(tempNode);
				}
			}
		}
		traverseScenerioOne(temp->next, list, Destination, date, airLine,time);
		return;
	}
}


void Graph::scenerioTwo(string Source, string Destination, Date& date, List* directFlights, List* indirectFlights, List* indirectFlightsHead, Vector<string>* indirectflightSource, Vector<string>* indirectFlightsHeadSource)				//The function handeling all the requests regarding Scenerio one
{
	int index = source_name.find(Source);
	node* temp = source[index].head;
	traverseScenerioTwo(temp, directFlights, Destination, date);			//Calculate the direct flights to all the destinations
	
	Vector<string> visitedLocations;

	while (temp != NULL)
	{
		if (temp->destination != Destination)
		{
			if (visitedLocations.find(temp->destination) == -1)
			{
				visitedLocations.insert(temp->destination);
				List* tempList = new List();
				bool flightCheck = traverseScenerioTwo(temp, temp->destination, date, tempList);
				if (flightCheck)
				{
					node* temp_two = tempList->head;
					while (temp_two != NULL)
					{
						int index_one = source_name.find(temp->destination);
						if (index_one != -1)
						{
							node* temp_one = source[index_one].head;
							int temp_size = indirectFlights->getSize();
							traverseScenerioTwo(temp_one, indirectFlights, Destination, date, temp_two->time_arrival[0]);
							if (temp_size < indirectFlights->getSize())
							{
								while (temp_size < indirectFlights->getSize())
								{
									indirectFlightsHeadSource->insert(source_name[index]);
									indirectflightSource->insert(source_name[index_one]);
									indirectFlightsHead->insert_end(temp_two);
									temp_size++;
								}
							}
						}
						temp_two = temp_two->next;
					}
				}
			}
		}
		temp = temp->next;
	}

	sortTime(directFlights);					//Sort the direct flights with respect to time difference
	
	if (directFlights->head == NULL)
	{
		cout << "No Direct Flights available.\n";
	}
	else
	{
		node* temp = directFlights->head;
		cout << "Direct Flights available.\n\n";
		for (int a = 0; temp != NULL; a++)
		{
			cout << "Flight" << a + 1 << endl;
			cout << Source << " " << temp->destination << " " << date.get_Date() << " " << temp->time_departure[0].get_Time() << " " << temp->time_arrival[0].get_Time() << " " << temp->cost[0] << " " << temp->air_line[0] << endl << endl;
			temp = temp->next;
		}
	}

	sortTime(indirectFlights, indirectFlightsHead, indirectflightSource, indirectFlightsHeadSource);

	if (indirectFlights->head == NULL)
	{
		cout << "\nNo Connected Flights available.\n";
	}
	else
	{

		node* temp = indirectFlights->head;
		node* temp_one = indirectFlightsHead->head;
		cout << "\nConnected Flights available.\n";
		for (int a = 0; temp != NULL && temp_one != NULL; a++)
		{
			cout << "Flight " << a + 1 << endl;
			if (indirectFlightsHeadSource[0].Size() > a)
			{
				cout << indirectFlightsHeadSource[0][a] << " ";
			}
			cout << temp_one->destination << " " << date.get_Date() << " " << temp_one->time_departure[0].get_Time() << " " << temp_one->time_arrival[0].get_Time() << " " << temp_one->cost[0] << " " << temp_one->air_line[0] << " " << temp_one->Stay_charges << endl;
			if (indirectflightSource[0].Size() > a)
			{
				cout << indirectflightSource[0][a] << " ";
			}
			cout << temp->destination << " " << date.get_Date() << " " << temp->time_departure[0].get_Time() << " " << temp->time_arrival[0].get_Time() << " " << temp->cost[0] << " " << temp->air_line[0] << " " << temp->Stay_charges << endl;
			temp = temp->next;
			temp_one = temp_one->next;
		}
	}
	return;
}


void Graph::traverseScenerioTwo(node* temp, List* list, string Destination, Date& date)							//Helping function for Scenerio Two
{
	if (temp == NULL)
	{
		return;
	}
	else
	{
		int index = temp->date.Size();
		for (int a = 0; a < index; a++)
		{
			
			if (temp->time_departure[a].get_Hours() >= 0 && temp->time_arrival[a].get_Hours() < 24)
			{
				if (temp->destination == Destination && temp->date[a].get_Date() == date.get_Date())
				{
					node* tempNode = createNode(Destination, temp->cost[a], temp->Stay_charges, date, temp->time_departure[a], temp->time_arrival[a], temp->air_line[a]);
					list->insert_end(tempNode);
				}
			}
		}
		traverseScenerioTwo(temp->next, list, Destination, date);
		return;
	}
}


bool Graph::traverseScenerioTwo(node* temp, string Destination, Date& date, List* list)			//Helping function for Scenerio Two
{
	int index = temp->date.Size();
	for (int a = 0; a < index; a++)
	{
		if (temp->time_departure[a].get_Hours() >= 0 && temp->time_arrival[a].get_Hours() < 24)
		{
			if (temp->destination == Destination && temp->date[a].get_Date() == date.get_Date())
			{
				node* tempNode = createNode(Destination, temp->cost[a], temp->Stay_charges, date, temp->time_departure[a], temp->time_arrival[a], temp->air_line[a]);
				list->insert_end(tempNode);
			}
		}
	}
	if (list->isEmpty())
	{
		return false;
	}
	else
	{
		return true;
	}
}


void Graph::traverseScenerioTwo(node* temp, List* list, string Destination, Date& date, Time& time)							//Helping function for Scenerio two
{
	if (temp == NULL)
	{
		return;
	}
	else
	{
		int index = temp->air_line.Size();
		for (int a = 0; a < index; a++)
		{
			if (temp->time_departure[a].get_Hours() >= 0 && temp->time_arrival[a].get_Hours() < 24)
			{
				if (temp->destination == Destination && temp->date[a].get_Date() == date.get_Date() && temp->time_departure[a].get_Hours() > time.get_Hours())
				{
					node* tempNode = createNode(Destination, temp->cost[a], temp->Stay_charges, date, temp->time_departure[a], temp->time_arrival[a], temp->air_line[a]);
					if (!list->duplicate(tempNode))
					{
						list->insert_end(tempNode);
					}
				}
			}
		}
		traverseScenerioTwo(temp->next, list, Destination, date, time);
		return;
	}
}


void Graph::sortTime(List* list)												//Helping function for sorting the data with  respect to time difference
{
	node* temp = list->head;
	if (temp != NULL)
	{
		while (temp->next != NULL)
		{
			node* temp_one = temp->next;
			while (temp_one != NULL)
			{
				if (abs(temp->time_departure[0].get_Hours() - temp->time_arrival[0].get_Hours()) > abs(temp_one->time_departure[0].get_Hours() - temp_one->time_arrival[0].get_Hours()))
				{
					string tempDest = temp->destination;
					int tempCost = temp->cost[0];
					Time temptimeDepart = temp->time_departure[0];
					Time temptimeArr = temp->time_arrival[0];
					string tempAir = temp->air_line[0];
					int tempStayCharge = temp->Stay_charges;
					Date tempDate = temp->date[0];

					temp->destination = temp_one->destination;
					temp->air_line[0] = temp_one->air_line[0];
					temp->cost[0] = temp_one->cost[0];
					temp->date[0] = temp_one->date[0];
					temp->Stay_charges = temp_one->Stay_charges;
					temp->time_departure[0] = temp_one->time_departure[0];
					temp->time_arrival[0] = temp_one->time_arrival[0];

					temp_one->destination = tempDest;
					temp_one->air_line[0] = tempAir;
					temp_one->cost[0] = tempCost;
					temp_one->date[0] = tempDate;
					temp_one->Stay_charges = tempStayCharge;
					temp_one->time_departure[0] = temptimeDepart;
					temp_one->time_arrival[0] = temptimeArr;
				}
				temp_one = temp_one->next;
			}
			temp = temp->next;
		}
	}
}


void Graph::sortCost(List* list1, List* list2, Vector<string>* indirect1, Vector<string>* indirect2)									//Sort the list on the basis of cost
{
	node* temp = list1->head;
	node* temp_two = list2->head;
	int count1 = 0, count2 =0;
	if (temp != NULL && temp_two != NULL)
	{
		while (temp->next != NULL && temp_two->next != NULL)
		{
			node* temp_one = temp->next;
			node* temp_three = temp_two->next;
			count2 = count1;
			while (temp_one != NULL && temp_three != NULL)
			{
				if ((temp->cost[0] + temp_two->cost[0]) > (temp_one->cost[0] + temp_three->cost[0]))
				{
					//For temp and temp_one (list1) 
					string tempDest = temp->destination;
					int tempCost = temp->cost[0];
					Time temptimeDepart = temp->time_departure[0];
					Time temptimeArr = temp->time_arrival[0];
					string tempAir = temp->air_line[0];
					int tempStayCharge = temp->Stay_charges;
					Date tempDate = temp->date[0];

					temp->destination = temp_one->destination;
					temp->air_line[0] = temp_one->air_line[0];
					temp->cost[0] = temp_one->cost[0];
					temp->date[0] = temp_one->date[0];
					temp->Stay_charges = temp_one->Stay_charges;
					temp->time_departure[0] = temp_one->time_departure[0];
					temp->time_arrival[0] = temp_one->time_arrival[0];

					temp_one->destination = tempDest;
					temp_one->air_line[0] = tempAir;
					temp_one->cost[0] = tempCost;
					temp_one->date[0] = tempDate;
					temp_one->Stay_charges = tempStayCharge;
					temp_one->time_departure[0] = temptimeDepart;
					temp_one->time_arrival[0] = temptimeArr;					
					
					//for temp_two and temp_three (list2)
					tempDest = temp_two->destination;
					tempCost = temp_two->cost[0];
					temptimeDepart = temp_two->time_departure[0];
					temptimeArr = temp_two->time_arrival[0];
					tempAir = temp_two->air_line[0];
					tempStayCharge = temp_two->Stay_charges;
					tempDate = temp_two->date[0];

					temp_two->destination = temp_three->destination;
					temp_two->air_line[0] = temp_three->air_line[0];
					temp_two->cost[0] = temp_three->cost[0];
					temp_two->date[0] = temp_three->date[0];
					temp_two->Stay_charges = temp_three->Stay_charges;
					temp_two->time_departure[0] = temp_three->time_departure[0];
					temp_two->time_arrival[0] = temp_three->time_arrival[0];

					temp_three->destination = tempDest;
					temp_three->air_line[0] = tempAir;
					temp_three->cost[0] = tempCost;
					temp_three->date[0] = tempDate;
					temp_three->Stay_charges = tempStayCharge;
					temp_three->time_departure[0] = temptimeDepart;
					temp_three->time_arrival[0] = temptimeArr;

					//Changing the values of the vector as well
					string temp1 = indirect1[0][count1];
					indirect1[0][count1] = indirect1[0][count1 + 1];
					indirect1[0][count1 + 1] = temp1;

					temp1 = indirect2[0][count1];
					indirect2[0][count1] = indirect2[0][count1 + 1];
					indirect2[0][count1 + 1] = temp1;

				}
				temp_one = temp_one->next;
				temp_three = temp_three->next;
				count2++;
			}
			temp = temp->next;
			temp_two = temp_two->next;
			count1++;
		}
	}
}


void Graph::sortTime(List* list1, List* list2, Vector<string>* indirect1, Vector<string>* indirect2)												//Helping function for sorting the data with respect to time difference
{
	node* temp = list1->head;
	node* temp_two = list2->head;
	int count1 = 0, count2 = 0;
	if (temp != NULL && temp_two != NULL)
	{
		while (temp->next != NULL && temp_two->next != NULL)
		{
			node* temp_one = temp->next;
			node* temp_three = temp_two->next;
			count2 = count1;
			while (temp_one != NULL && temp_three != NULL)
			{
				if ((abs(temp->time_departure[0].get_Hours() - temp->time_arrival[0].get_Hours()) + abs(temp_two->time_departure[0].get_Hours() - temp_two->time_arrival[0].get_Hours())) > (abs(temp_one->time_departure[0].get_Hours() - temp_one->time_arrival[0].get_Hours()) + abs(temp_three->time_departure[0].get_Hours() - temp_three->time_arrival[0].get_Hours())))
				{
					//For temp and temp_one (list1) 
					string tempDest = temp->destination;
					int tempCost = temp->cost[0];
					Time temptimeDepart = temp->time_departure[0];
					Time temptimeArr = temp->time_arrival[0];
					string tempAir = temp->air_line[0];
					int tempStayCharge = temp->Stay_charges;
					Date tempDate = temp->date[0];

					temp->destination = temp_one->destination;
					temp->air_line[0] = temp_one->air_line[0];
					temp->cost[0] = temp_one->cost[0];
					temp->date[0] = temp_one->date[0];
					temp->Stay_charges = temp_one->Stay_charges;
					temp->time_departure[0] = temp_one->time_departure[0];
					temp->time_arrival[0] = temp_one->time_arrival[0];

					temp_one->destination = tempDest;
					temp_one->air_line[0] = tempAir;
					temp_one->cost[0] = tempCost;
					temp_one->date[0] = tempDate;
					temp_one->Stay_charges = tempStayCharge;
					temp_one->time_departure[0] = temptimeDepart;
					temp_one->time_arrival[0] = temptimeArr;

					//for temp_two and temp_three (list2)
					tempDest = temp_two->destination;
					tempCost = temp_two->cost[0];
					temptimeDepart = temp_two->time_departure[0];
					temptimeArr = temp_two->time_arrival[0];
					tempAir = temp_two->air_line[0];
					tempStayCharge = temp_two->Stay_charges;
					tempDate = temp_two->date[0];

					temp_two->destination = temp_three->destination;
					temp_two->air_line[0] = temp_three->air_line[0];
					temp_two->cost[0] = temp_three->cost[0];
					temp_two->date[0] = temp_three->date[0];
					temp_two->Stay_charges = temp_three->Stay_charges;
					temp_two->time_departure[0] = temp_three->time_departure[0];
					temp_two->time_arrival[0] = temp_three->time_arrival[0];

					temp_three->destination = tempDest;
					temp_three->air_line[0] = tempAir;
					temp_three->cost[0] = tempCost;
					temp_three->date[0] = tempDate;
					temp_three->Stay_charges = tempStayCharge;
					temp_three->time_departure[0] = temptimeDepart;
					temp_three->time_arrival[0] = temptimeArr;

					//Changing the values of the vector as well
					string temp1 = indirect1[0][count1];
					indirect1[0][count1] = indirect1[0][count1 + 1];
					indirect1[0][count1 + 1] = temp1;

					temp1 = indirect2[0][count1];
					indirect2[0][count1] = indirect2[0][count1 + 1];
					indirect2[0][count1 + 1] = temp1;

				}
				temp_one = temp_one->next;
				temp_three = temp_three->next;
				count2++;
			}
			temp = temp->next;
			temp_two = temp_two->next;
			count1++;
		}
	}
}


void Graph::Scenerio_5(List* flights, Vector<string>& source_n, string src, string dest, Date dt)
{
	node* start = new node;
	int index = 0;
	for (int i = 0; i < source_name.Size(); i++)
	{
		if (source_name[i] == src)
		{
			index = i;
			start = source[i].head;
			i += source_name.Size();
		}
	}
	while (start != NULL)
	{
		if (start->destination == dest )
		{
			int idx = start->date.Size();
			for (int i = 0; i < idx; i++)
			{
				if (start->date[i] == dt)
				{
					node* temp = new node;
					temp->destination = start->destination;
					temp->date.insert(start->date[i]);
					temp->cost.insert(start->cost[i]);
					temp->Stay_charges = start->Stay_charges;
					temp->time_arrival.insert(start->time_arrival[i]);
					temp->time_departure.insert(start->time_departure[i]);
					temp->air_line.insert(start->air_line[i]);
					if (flights->duplicate(temp) == false)
					{
						source_n.insert(source_name[index]);
						flights->insert_end(temp);
					}
				}
			}
		}
		start = start->next;
	}
	return;
}


void Graph::scenerioFour(string Source, string Destination, Date& date, string TransitLocation, int waitDuration, List* indirectFlights, List* indirectFlightsHead, Vector<string>* indirectflightSource, Vector<string>* indirectFlightsHeadSource)				//The function handeling all the requests regarding Scenerio four
{
	int index = source_name.find(Source);
	node* temp = source[index].head;

	while (temp != NULL)
	{
		if (temp->destination != Destination && temp->destination == TransitLocation)
		{
			break;
		}
		temp = temp->next;
	}

	if (temp != NULL)
	{
		List* tempList = new List();
		bool flightCheck = traverseScenerioTwo(temp, TransitLocation, date, tempList);
		if (flightCheck)
		{
			node* temp_two = tempList->head;
			while (temp_two != NULL)
			{
				int index_one = source_name.find(temp->destination);
				if (index_one != -1)
				{
					node* temp_one = source[index_one].head;
					int temp_size = indirectFlights->getSize();
					traverseScenerioTwo(temp_one, indirectFlights, Destination, date, temp_two->time_arrival[0]);
					if (indirectFlights->head != NULL)
					{
						if (abs(temp_two->time_arrival[0].get_Hours() - indirectFlights->tail->time_departure[0].get_Hours()) < waitDuration)
						{
							while (temp_size < indirectFlights->getSize())
							{
								indirectFlightsHeadSource->insert(source_name[index]);
								indirectflightSource->insert(source_name[index_one]);
								indirectFlightsHead->insert_end(temp_two);
								temp_size++;
							}
						}
						else
						{
							indirectFlights->pop();
						}
					}
				}
				temp_two = temp_two->next;
			}
		}
	}

	sortTime(indirectFlights, indirectFlightsHead, indirectflightSource, indirectFlightsHeadSource);
/*
	if (indirectFlights->head == NULL)
	{
		cout << "\nNo Connected Flights available.\n";
	}
	else
	{

		node* temp = indirectFlights->head;
		node* temp_one = indirectFlightsHead->head;
		cout << "\nConnected Flights available.\n";
		for (int a = 0; temp != NULL && temp_one != NULL; a++)
		{
			cout << "Flight " << a + 1 << endl;
			if (indirectFlightsHeadSource->Size() > a)
			{
				cout << indirectFlightsHeadSource[0][a] << " ";
			}
			cout << temp_one->destination << " " << date.get_Date() << " " << temp_one->time_departure[0].get_Time() << " " << temp_one->time_arrival[0].get_Time() << " " << temp_one->cost[0] << " " << temp_one->air_line[0] << " " << temp_one->Stay_charges << endl;
			if (indirectflightSource[0].Size() > a)
			{
				cout << indirectflightSource[0][a] << " ";
			}
			cout << temp->destination << " " << date.get_Date() << " " << temp->time_departure[0].get_Time() << " " << temp->time_arrival[0].get_Time() << " " << temp->cost[0] << " " << temp->air_line[0] << " " << temp->Stay_charges << endl;
			temp = temp->next;
			temp_one = temp_one->next;
		}
	}*/
	return;
}


#endif