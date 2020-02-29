#ifndef VECTOR_H
#define VECTOR_H


#include<iostream>
#include<string>
using namespace std;


template<typename name>
class Vector			// templatized vector class
{

	public:
		name* arr;			// array to store values
		int s;					// integer to store size

		Vector();
		void insert(name);
		int Size();
		void display();
		void Clear();
		int find(name);
		bool isEmpty();
		name pop();
		name pop(name);
		name& operator[](int);
		Vector<name> operator=(Vector<name>);

};


template<typename name>
int Vector<name>::find(name x)				//returns position of key in vector
{
	for (int i = 0; i < s; i++)
	{
		if (arr[i] == x)
		{
			return i;
		}
	}
	return -1;
}


template<typename name>
Vector<name> Vector<name>::operator=(Vector<name> v)		// assignment operator overloading
{
	this->Clear();
	for (int i = 0; i < v.s; i++) this->insert(v[i]);
	return *this;
}


template<typename name>
Vector<name>::Vector()
{
	s = 0;
}


template<typename name>
void Vector<name> ::insert(name val)				//inserting value at end
{
	if (s == 0)
	{
		s = 1;
		arr = new name[1];
		arr[0] = val;
	}
	else if (s > 0)
	{
		name* temp;
		temp = new name[s + 1];
		for (int i = 0; i < s; i++)
		{
			temp[i] = arr[i];
		}
		temp[s] = val;
		delete[] arr;
		s++;
		arr = new name[s];
		for (int i = 0; i < s; i++)
		{
			arr[i] = temp[i];
		}
	}
	return;
}


template<typename name>
void Vector<name>::display()		//displays full vector
{
	for (int i = 0; i < s; i++)	cout << i + 1 << " " << arr[i] << endl;
	return;
}


template<typename name>
int Vector<name>::Size()		//returns size
{
	return s;
}


template<typename name>
void Vector<name>::Clear()		//clears vector
{
	s = 0;
	delete[] arr;
	return;
}


template<class name>
name& Vector<name>::operator[](int i)		//index operator over loading
{
	return arr[i];
}


template <class name>
bool Vector<name>::isEmpty()
{
	if (s == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


template <class name>
name Vector<name>::pop()
{
	if (s >0)
	{
		name* temp = new name[s - 1];
		name val = arr[s - 1];
		for (int a = 0; a < s - 1; a++)
		{
			temp[a] = arr[a];
		}
		s--;
		delete arr;
		arr = new name[s];
		for (int a = 0; a < s; a++)
		{
			arr[a] = temp[a];
		}
		delete temp;
		return val;
	}
}


template <class name>
name Vector<name>::pop(name val)
{
	int index = find(val);
	for (int a = 0; a < s-1; a++)
	{
		if (a >= index)
		{
			arr[a] = arr[a + 1];
		}
	}
	return val;
}


#endif