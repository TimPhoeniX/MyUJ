#include "obj.hpp"
#include<iostream>
#include<unistd.h>

int main()
{
	PREDATOR a(1,1,1,1);
	VICTIM b(2,2,2,2);
	distance(a,b);
	WORLD X;
	X.addPredator(1,1,1,1);
	X.addVictim(5,6,2,2);
	try
	{
		X.distance(X.getPredator(0),X.getVictim(0));
	}
	catch(std::string e)
	{
		std::cout << "Wyjątek: "+e+'\n';
	}
	try
	{
		X.distance(X.getPredator(2),X.getVictim(0));
	}
	catch(std::string e)
	{
		std::cout << "Wyjątek: "+e+'\n';
	}
	try
	{
		X.distance(X.getPredator(0),X.getVictim(2));
	}
	catch(std::string e)
	{
		std::cout << "Wyjątek: "+e+'\n';
	}
	try
	{
		X.distance(b,X.getVictim(0));
	}
	catch(std::string e)
	{
		std::cout << "Wyjątek: "+e+'\n';
	}
	
}