#include<iostream>
#include<iomanip>
#include "Miasto.hpp"

/* Miasto::Miasto()
{
	std::cout << "Podaj nazwę: ";
	std::cin >> nazwa;
	std::cout << "Podaj liczbę ludności: ";
	std::cin >> ludnosc;
	std::cout << "Podaj długość (stopnie minuty sekundy) (Jeśli współrzędne ujemne przed każda daj -): ";
	double stopnie=0, minuty=0, sekundy=0;
	std::cin >> stopnie >> minuty >> sekundy;
	double temp=stopnie + minuty/60 + sekundy/3600;
	if(temp > 90 || temp < -90 )
		std::cout << "BŁĄD\n";
	szerokosc=temp;
	std::cout << "Podaj długość (stopnie minuty sekundy) (Jeśli współrzędne ujemne przed każda daj -): ";
	std::cin >> stopnie >> minuty >> sekundy;
	temp=stopnie + minuty/60 + sekundy/3600;
	if (temp > 180 || temp < -180 )
		std::cout << "BŁĄD\n";
	dlugosc=temp;
}*/

Miasto::Miasto()
{
	nazwa="\0";
	ludnosc=0;
	szerokosc=0;
	dlugosc=0;
}

// Miasto::Miasto(std::string name, int people, double s1, double s2 ,double s3 ,double d1,double d2 ,double d3)
// {
// 	nazwa = name;
// 	ludnosc = people;
// 	szerokosc=s1 + s2/60 + s3/3600;
// 	if(szerokosc > 90 || szerokosc < -90 )
// 		std::cout << "BŁĄD\n";
// 	dlugosc=d1 + d2/60 + d3/3600;
// 	if (dlugosc > 180 || dlugosc < -180 )
// 		std::cout << "BŁĄD\n";
// }

Miasto::Miasto(std::string name, int people, double s1, double s2 ,double s3 ,double d1,double d2 ,double d3)
: nazwa(name), ludnosc(people), szerokosc(s1 + s2/60 + s3/3600), dlugosc(d1 + d2/60 + 3/3600)
{
	if(szerokosc > 90 || szerokosc < -90 )
		std::cout << "BŁĄD\n";
	if (dlugosc > 180 || dlugosc < -180 )
		std::cout << "BŁĄD\n";
}

Miasto::~Miasto() {}

void Miasto::pokaz()
{
	std::cout << "Nazwa: "+nazwa+"\n";
	std::cout << "Liczba ludności: " << ludnosc << '\n';
	std::cout << "Szerokość: ";
	if( szerokosc <= 90 && szerokosc > 0)
	{
		std::cout << szerokosc << " N\n";
	}
	else if (szerokosc < 0 && szerokosc >= -90)
	{
		std::cout << szerokosc << " S\n";
	}
	else if( szerokosc == 0)
	{
		std::cout<< szerokosc << '\n';
	}
	else std::cout << "BŁĄD\n";
	std::cout << "Długość: ";
	if( dlugosc <= 180 && dlugosc >= 0)
	{
		std::cout << dlugosc << " E\n";
	}
	else if (dlugosc < 0 && dlugosc >= -180)
	{
		std::cout << dlugosc << " W\n";
	}
	else std::cout << "BŁĄD\n";
}

void Miasto::zmiennazwe(std::string name)
{
	nazwa=name;
}

void Miasto:: zmienludnosc(int people)
{
	ludnosc=people;
}

void Miasto::zmienpolozenie(double s1, double s2 ,double s3 ,double d1,double d2 ,double d3)
{
	szerokosc=s1 + s2/60 + s3/3600;
	if(szerokosc > 90 || szerokosc < -90 )
		std::cout << "BŁĄD\n";
	dlugosc=d1 + d2/60 + d3/3600;
	if (dlugosc > 180 || dlugosc < -180 )
		std::cout << "BŁĄD\n";
}