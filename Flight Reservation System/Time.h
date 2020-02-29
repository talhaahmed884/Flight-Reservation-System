#ifndef TIME_H
#define TIME_H


#include<iostream>
#include<cstring>
#include<sstream>
#include<string>
using namespace std;


class Time
{

	private:

		int hours;
		int minutes;

	public:
	
		Time();
		Time(int, int);
		string get_Time();
		void set_Time(string);
		int get_Hours();
		int get_Minutes();
		void set_Hours(int);
		void set_Minutes(int);
		void convert(string, string);
		friend ostream& operator << (ostream& out, Time& d);

};


Time::Time()
{
	hours = 0;
	minutes = 0;
}


Time::Time(int x, int y)
{
	hours = x;
	minutes = y;
}


string Time::get_Time()
{
	string str;
	str += to_string(hours);
	str += ":";
	if (minutes < 10)str += '0';
	str += to_string(minutes);
	return str;
}


void Time::set_Time(string str)
{
	string m;
	string h;
	int check = 0;
	int i = 0;
	int	len = str.length();
	while (i < len)
	{
		if (str[i] == ':')check++;
		else if (check == 0)h += str[i];
		else if (check == 1)m += str[i];
		i++;
	}
	convert(h, m);
	return;
}


void Time::convert(string h, string m)
{
	stringstream geek1(h);
	geek1 >> hours;
	stringstream geek2(m);
	geek2 >> minutes;
	return;
}


int Time::get_Hours()
{
	return hours;
}


int Time::get_Minutes()
{
	return minutes;
}


void Time::set_Hours(int x)
{
	hours = x;
	return;
}


void Time::set_Minutes(int x)
{
	minutes = x;
	return;
}


ostream& operator << (ostream& out, Time& d)
{
	out << d.get_Time();
	return out;
}


#endif