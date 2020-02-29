#ifndef DATE_H
#define DATE_H


#include<iostream>
#include<string>
#include<sstream>
#include<cstring>
using namespace std;


class Date
{

	private:
		int day;
		int month;
		int year;

	public:

		Date();
		Date(int, int, int);

		void set_Date(string);
		void set_Day(int);
		void set_Month(int);
		void set_Year(int);
		int get_Day();
		int get_Month();
		int get_Year();
		string get_Date();
		void convert(string d, string m, string y);
		bool operator==(const Date&);
		friend ostream& operator << (ostream& out, Date& d);

};


Date::Date()
{
	day = 0;
	month = 0;
	year = 0;
}


Date::Date(int x, int y, int z)
{
	day = x;
	month = y;
	year = z;
}


void Date::convert(string d, string m, string y)
{
	stringstream geek1(d);
	geek1 >> day;
	stringstream geek2(m);
	geek2 >> month;
	stringstream geek3(y);
	geek3 >> year;
	return;
}


void Date::set_Date(string str)
{
	int i = 0;
	int check = 0;
	string d;
	string m;
	string y;
	int len = str.length() ;
	while (i < len)
	{
		if (str[i] == '/') check++;
		else if (check == 0)d += str[i];
		else if (check == 1)m += str[i];
		else if (check == 2)y += str[i];
		i++;
	}
	convert(d, m, y);
	return;
}


void Date::set_Day(int x)
{
	day = x;
	return;
}


void Date::set_Month(int x)
{
	month = x;
	return;
}


void Date::set_Year(int x)
{
	year = x;
	return;
}


int Date::get_Day()
{
	return day;
}


int Date::get_Month()
{
	return month;
}


int Date::get_Year()
{
	return year;
}


string Date::get_Date()
{
	string str;
	str += to_string(day);
	str += "/";
	str += to_string(month);
	str += "/";
	str += to_string(year);
	return str;
}

bool Date::operator==(const Date& dt)
{
	if (day == dt.day && month == dt.month && year == dt.year)return true;
	return false;
}
ostream& operator << (ostream& out, Date& d)
{
	out << d.get_Date();
	return out;
}


#endif