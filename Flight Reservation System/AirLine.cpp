#include "Graph.h"

string convert(string str);
void Display(node*);
void Display_3(node*);
void Display_4(node*, node*);
int main()
{
	char conti = 'Y';

	Graph graph;
	string fli = "Flights.txt";
	string hotelCharges = "HotelCharges_perday.txt";
	graph.createGraph(hotelCharges,fli);
	system("CLS");
	cout << "======================================================================================================== \n";
	cout << "==========================FLIGHT RESERVATION SYSTEM===================================================== \n";
	cout << "======================================================================================================== \n";
	cout << "\n\n\n";
	cout << "Do you want to book a flight? \n 1) Y for yes \n 2)N for NO \n";
	cin >> conti;

	while (conti == 'Y' || conti == 'y')
	{
		char trans = '-';
		string origin = "-";
		string destination = "-";
		string transit = "-";
		string airline = "-";
		Date dt;
		Vector<string> origin_name;
		int stay = -1, day, month, line = -1, year = -1;

		system("CLS");
		if (conti == 'Y' || conti == 'y')
		{
			system("CLS");
			cout << "\n\n           WELCOME TO FLIGHT RESERVATION SYSTEM \n\n\n";
			cout << "\n Enter your origin   ";
			cin >> origin;
			origin = convert(origin);
			cout << "\n Enter your Destination   ";
			cin >> destination;
			destination = convert(destination);
			cout << "\n Enter Day  ";
			cin >> day;
			cout << "\n Enter Month   ";
			cin >> month;
			cout << "\n Enter Year   ";
			cin >> year;
			dt.set_Day(day);
			dt.set_Month(month);
			dt.set_Year(year);
			cout << "\n Do you want any transit location? \n 1) Y for yes \n 2)N for NO \n";
			cin >> trans;
			if (trans == 'Y' || trans == 'y')
			{
				cout << "\n Enter transit location ";
				cin >> transit;
				transit = convert(transit);
				cout << "\n Do you wan to stay at your transit location? \n 1) Y for yes \n 2)N for NO \n";
				cin >> trans;
				if (trans == 'Y' || trans == 'y')
				{
					cout << "\n Enter Duration in hours ";
					cin >> stay;
				}
			}
			cout << "\n Do you want to select airline of your choice? \n 1) Y for yes \n 2)N for NO \n";
			cin >> trans;
			if (trans == 'Y' || trans == 'y')
			{
				cout << " Press 1 for Emirates \n  Press 2 for Qatar \n  Press 2 for ANA \n";
				cin >> line;
				if (line == 1)airline = "Emirates";
				else if (line == 2)airline = "Qatar";
				else if (line == 3)airline = "ANA";
			}
		}
		if (origin != "-" && destination != "-" && year != -1 && stay == -1 && transit == "-" && airline == "-")	// done
		{
			List* flights = new List;
			system("CLS");
			graph.Scenerio_5(flights, origin_name, origin, destination, dt);
			if (flights->head != NULL)
			{
				cout << "direct flights from " << origin << " to " << destination << " are:\n";
				Display(flights->head);
			}
			else
			{
				int temp = dt.get_Day();
				flights->clear();
				cout << "No Flights available on " << dt.get_Date() << "\n Suggested flights are:\n";
				dt.set_Day(temp + 1);
				graph.Scenerio_5(flights, origin_name, origin, destination, dt);
				dt.set_Day(temp - 1);
				graph.Scenerio_5(flights, origin_name, origin, destination, dt);
				cout << "direct flights from " << origin << " to " << destination << " are:\n";
				Display(flights->head);
			}
		}

		else if (origin != "-" && destination != "-" && year != -1 && transit != "-" && stay ==-1 && airline == "-")	// done
		{
			List* flights = new List;
			system("CLS");
			cout << "FLIGHTS FROM ORIGIN TO TRANSIT \n";
			graph.Scenerio_5(flights, origin_name, origin, transit, dt);
			if (flights->head != NULL)
			{
				cout << "direct flights from " << origin << " to " << transit << " are:\n";
				Display_3(flights->head);
			}
			else
			{
				int temp = dt.get_Day();
				flights->clear();
				cout << "No Flights available on " << dt.get_Date() << "\n Suggested flights are:";
				Date t(dt.get_Day() + 1, dt.get_Month(),dt.get_Year());
				graph.Scenerio_5(flights, origin_name, origin, transit, t);
				Date p(dt.get_Day() - 1, dt.get_Month(), dt.get_Year());
				graph.Scenerio_5(flights, origin_name, origin, transit, p);
				cout << "direct flights from " << origin << " to " << transit << " are:\n";
				Display_3(flights->head);
			}

			cout << "\n FLIGHTS FROM TRANSIT TO DESTINATION \n";
			graph.Scenerio_5(flights, origin_name, transit, destination, dt);
			if (flights->head != NULL)
			{
				cout << "direct flights from " << transit << " to " << destination << " are:\n";
				Display(flights->head);
			}
			else
			{
				int temp = dt.get_Day();
				flights->clear();
				cout << "No Flights available on " << dt.get_Date() << "\n Suggested flights are:";
				Date t(dt.get_Day() + 1, dt.get_Month(), dt.get_Year());

				graph.Scenerio_5(flights, origin_name, transit, destination, t);
				
				Date p(dt.get_Day() - 1, dt.get_Month(), dt.get_Year());
				graph.Scenerio_5(flights, origin_name, transit,destination, p);
				cout << "direct flights from " << transit << " to " << destination << " are:\n";
				Display(flights->head);
			}
		}

		else if (origin != "-" && destination != "-" && year != -1 && transit != "-" && stay != -1 && airline == "-")	// done
		{
			List* flights = new List;
			List* flights_head = new List;
			Vector<string> flightSource ;
			Vector<string> FlightsHeadSource;
			system("CLS");
			cout << "Scenerio 4 \n"; 
			graph.scenerioFour(origin, destination, dt, transit, stay, flights, flights_head, &flightSource, &FlightsHeadSource);
			if (flights_head->head != NULL)
			{
				cout << "Flights from " << origin << " to" << destination << " alon with stay at" << transit << " are :\n";
				Display_4(flights->head,flights_head->head);
			}
			else
			{
				cout << "NO flights avaiable on " << dt.get_Date() << " \n";
				cout << "\n Suggested fligts are: ";
				flights->clear();
				flights_head->clear();
				flightSource.Clear();
				FlightsHeadSource.Clear();
				Date t(dt.get_Day() + 1, dt.get_Month(), dt.get_Year());
				graph.scenerioFour(origin, destination, t, transit, stay, flights, flights_head, &flightSource, &FlightsHeadSource);
				Date p(dt.get_Day() + 1, dt.get_Month(), dt.get_Year());
				graph.scenerioFour(origin, destination, p, transit, stay, flights, flights_head, &flightSource, &FlightsHeadSource);

				Display_4(flights->head , flights_head->head);
			}
		}
		else if (origin != "-" && destination != "-" && year != -1 && stay == -1 && transit == "-" && airline != "-")	// done
		{
			system("CLS");
			List* Direct = new List;
			List* indirect_transit = new List;
			List* indirect_Destination = new List;
			Vector<string> indirectflightSource;
			Vector<string> indirectFlightsHeadSource;
			//cout << "Scenerio 1 \n";
			//scenerioOne(string Source, string Destination, Date& date, string airLine, List* directFlights, 
			//	List* indirectFlights, List* indirectFlightsHead, 
			//	Vector<string>* indirectflightSource, Vector<string>* indirectFlightsHeadSource)
			graph.scenerioOne(origin, destination, dt, airline, Direct, indirect_transit, indirect_Destination,&indirectflightSource, &indirectFlightsHeadSource);
			if (Direct->head != NULL)
			{
				cout << "Direct Flights from " << origin << " to " << destination << " are:\n";
				Display(Direct->head);
			}
			else
			{
				cout << "No direct flights availble \n\n";
			}
			if (indirect_transit != NULL)
			{
				cout << "Connecting flights from " << origin << " to" << destination << "are: \n";
				Display_4(indirect_transit->head, indirect_Destination->head);
			}
		}
		else if (origin != "-" && destination != "-" && year != -1 && stay == -1 && transit != "-" && airline != "-")	// done
		{
			system("CLS");
			List* Direct = new List;
			List* indirect_transit = new List;
			List* indirect_Destination = new List;
			Vector<string> indirectflightSource;
			Vector<string> indirectFlightsHeadSource;
			//cout << "Scenerio 6 \n";				//not working  scenerio 3 with airline of choice
			graph.scenerioOne(origin, transit, dt, airline, Direct, indirect_transit, indirect_Destination, &indirectflightSource, &indirectFlightsHeadSource);
			if (Direct->head != NULL)
			{
				cout << "Flights form "<<origin<<"to "<<transit<<" are:\n";
				Display(Direct->head);
			}
			else
			{
				Direct->clear();
				cout << "Suggested Flights form " << origin << "to " << transit << " are:\n";
				Date p(dt.get_Day() + 1, dt.get_Month(), dt.get_Year());
				Date t(dt.get_Day() + 1, dt.get_Month(), dt.get_Year());
				graph.scenerioOne(origin, transit, t, airline, Direct, indirect_transit, indirect_Destination, &indirectflightSource, &indirectFlightsHeadSource);
				graph.scenerioOne(origin, transit, p, airline, Direct, indirect_transit, indirect_Destination, &indirectflightSource, &indirectFlightsHeadSource);
				Display(Direct->head);
			}
			graph.scenerioOne( transit,destination, dt, airline, Direct, indirect_transit, indirect_Destination, &indirectflightSource, &indirectFlightsHeadSource);
			if (Direct->head != NULL)
			{
				cout << "Flights form " << transit << "to " << destination << " are:\n";
				Display(Direct->head);
			}
			else
			{
				Direct->clear();
				cout << "Suggested Flights form " << transit << "to " << destination << " are:\n";
				Date p(dt.get_Day() + 1, dt.get_Month(), dt.get_Year());
				Date t(dt.get_Day() + 1, dt.get_Month(), dt.get_Year());
				graph.scenerioOne( transit,destination, t, airline, Direct, indirect_transit, indirect_Destination, &indirectflightSource, &indirectFlightsHeadSource);
				graph.scenerioOne( transit,destination, p, airline, Direct, indirect_transit, indirect_Destination, &indirectflightSource, &indirectFlightsHeadSource);
				Display(Direct->head);
			}
		}
		cout << "\n\n\n\n Do you want to book another flight? \n 1) Y for yes \n 2)N for NO \n";
		cin >> conti;
	}
	system("CLS");
	cout << "\n\n\n      THANK YOU!  \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
void Display(node* start)
{
	while (start != NULL)
	{
		int index = start->date.Size();
		for (int i = 0; i < index; i++)
		{
			cout << "\n Airline: " << start->air_line[i];
			cout << "\n Date: " << start->date[i] << "\n Arrival Time: " << start->time_arrival[i] << "\n Departure Time: " << start->time_departure[i];
			cout << "\n Cost: " << start->cost[i]<<endl<<endl;
		}
		start = start->next;
	}
}
void Display_4(node* start, node* start2)
{
	while (start != NULL)
	{
		int index = start->date.Size();
		for (int i = 0; i < index; i++)
		{
			cout << "\n Airline: " << start->air_line[i];
			cout << "\n Date: " << start->date[i] << "\n Arrival Time: " << start->time_arrival[i] << "\n Departure Time: " << start->time_departure[i];
			cout << "\n Cost: " << start->cost[i];
			cout << "Stay charges: " << start->Stay_charges << endl;

			cout << "\n Airline: " << start2->air_line[i];
			cout << "\n Date: " << start2->date[i] << "\n Arrival Time: " << start2->time_arrival[i] << "\n Departure Time: " << start2->time_departure[i];
			cout << "\n Cost: " << start2->cost[i];
			cout << "Stay charges: " << start2->Stay_charges << endl;
		}
		start2 = start2->next;
		start = start->next;
	}
}
void Display_3(node* start)
{
	while (start != NULL)
	{
		int index = start->date.Size();
		for (int i = 0; i < index; i++)
		{
			cout << "\n Airline: " << start->air_line[i];
			cout << "\n Date: " << start->date[i] << "\n Arrival Time: " << start->time_arrival[i] << "\n Departure Time: " << start->time_departure[i];
			cout << "\n Cost: " << start->cost[i];
			cout << "Stay charges: " << start->Stay_charges<<endl << endl;
		}
		start = start->next;
	}
}
string convert(string str)
{
	int len = str.length();
	int i = 0;
	while (i < len)
	{
		if (i == 0 && str[i] > 90)str[i] -= 32;
		else if (i > 0 && str[i] < 97)str[i] += 32;
		i++;
	}
	return str;
}