#include<iostream>
#include<iomanip>
#include<string>
#include "Vehicles.hpp"

POSITION::POSITION() : Szerokosc(0), Dlugosc(0) {}; 
POSITION::POSITION(double s1,double s2,double s3,double d1,double d2,double d3)
: Szerokosc(s1+s2/60+s3/3600), Dlugosc(d1+d2/60+d3/3600)
{
	if( Szerokosc > 90 || Szerokosc < -90 )

		std::cout << " BLAD ";
	if (Dlugosc > 180 || Dlugosc < -180 )

		std::cout << " BLAD ";
}
POSITION::~POSITION() {}
void POSITION::setSzerokosc(double s1,double s2,double s3)
{
	Szerokosc=(s1+s2/60+s3/3600);
	if( Szerokosc > 90 || Szerokosc < -90 )

		std::cout << " BLAD ";
}
void POSITION::setDlugosc(double d1,double d2,double d3)
{
	Dlugosc=(d1+d2/60+d3/3600);
	if (Dlugosc > 180 || Dlugosc < -180 )

		std::cout << " BLAD ";
}
void POSITION::show()
{
	if( Szerokosc <= 90 && Szerokosc > 0)
	{
		std::cout << std::fixed << std::setprecision(1) << Szerokosc << " N ";
	}
	else if (Szerokosc < 0 && Szerokosc >= -90)
	{
		std::cout << std::setprecision(1) << Szerokosc << " S ";
	}
	else if( Szerokosc == 0)
	{
		std::cout<< std::setprecision(1) << Szerokosc << ' ';
	}
	else std::cout << "BŁĄD  ";
	if( Dlugosc <= 180 && Dlugosc >= 0)
	{
		std::cout << std::setprecision(1) << Dlugosc << " E\n";
	}
	else if (Dlugosc < 0 && Dlugosc >= -180)
	{
		std::cout << std::setprecision(1) << Dlugosc << " W\n";
	}
	else std::cout << "BŁĄD\n";
}


unsigned int VEHICLE::Count = 0;
VEHICLE::VEHICLE() : ID(0), Name(""), Coords()
{
	incCount();
	std::cout << "Zbudowano VEHICLE. Licza VEHICLE = " << Count << '\n';
}
VEHICLE::VEHICLE(unsigned int id, std::string name, double s1,double s2,double s3,double d1,double d2,double d3)
: ID(id), Name(name), Coords(s1,s2,s3,d1,d2,d3)
{
	incCount();
	std::cout << "Zbudowano VEHICLE. Licza VEHICLE = " << Count << '\n';
}

VEHICLE::~VEHICLE()
{
	decCount();
	std::cout << "Zniszczono VEHICLE. Liczba VEHICLE = " << Count << '\n';
}
void VEHICLE::setCoords(double s1,double s2,double s3,double d1,double d2,double d3)
{
	Coords.setSzerokosc(s1,s2,s3);
	Coords.setDlugosc(d1,d2,d3);
}
void VEHICLE::setName(std::string name)
{
	Name=name;
}
void VEHICLE::setID(unsigned int id)
{
	ID=id;
}
void VEHICLE::show()
{
	std::cout << "Id: " << ID << " Nazwa: " << Name << '\n';
	std::cout << "Pozycja: ";
	Coords.show();
}
void VEHICLE::incCount()
{
	++Count;
}
void VEHICLE::decCount()
{
	--Count;
}

BUS::BUS() : Passangers(0), Drivers(0), DriverName(""), DriverSurname("")
{
	ID=0;
	Name="";
}
// BUS::BUS(unsigned int id,std::string name,double s1,double s2,double s3,double d1,double d2,double d3,
// 	unsigned int passangers, unsigned int drivers, std::string drivername, std::string driversurname)
// : Passangers(passangers), Drivers(drivers), DriverName(drivername), DriverSurname(driversurname)
// {
// 	ID=id;
// 	Name=name;
// // 	Coords.setSzerokosc(s1,s2,s3);
// // 	Coords.setDlugosc(d1,d2,d3);
// 	setCoords(s1,s2,s3,d1,d2,d3);
// }
BUS::BUS(unsigned int id,std::string name,double s1,double s2,double s3,double d1,double d2,double d3,
	unsigned int passangers, unsigned int drivers, std::string drivername, std::string driversurname)
: VEHICLE(id,name,s1,s2,s3,d1,d2,d3), Passangers(passangers), Drivers(drivers), DriverName(drivername), DriverSurname(driversurname) {}

BUS::~BUS()
{
	std::cout << "Zniszczono obiekt klasy BUS\n";
}
void BUS::setPassangers(int a)
{
	Passangers=a;
}
void BUS::setDrivers(int a)
{
	Drivers=a;
}
void BUS::setDriverName(std::string drivername)
{
	DriverName=drivername;
}
void BUS::setDriverSurname(std::string driversurname)
{
	DriverSurname=driversurname;
}
void BUS::show()
{
	std::cout << "Id: " << ID << " Nazwa: " << Name << '\n';
	std::cout << "Pozycja: ";
	Coords.show();
	std::cout << "Liczba pasażerów: " << Passangers << '\n';
	std::cout << "Liczba kierowców: " << Drivers << '\n';
	std::cout << "Dane kierowcy: "+DriverName+" "+DriverSurname+'\n';
}

TRUCK::TRUCK()
: Mass(0), CargoType("")
{
	ID=0;
	Name="";
}
// TRUCK::TRUCK(unsigned int id, std::string name, double s1,double s2,double s3,double d1,double d2,double d3,
// 			 double mass, std::string cargotype, std::string company)
// : Mass(mass), CargoType(cargotype), Company(company)
// {
// 	ID=id;
// 	Name=name;
// 	setCoords(s1,s2,s3,d1,d2,d3);
// }
TRUCK::TRUCK(unsigned int id, std::string name, double s1,double s2,double s3,double d1,double d2,double d3,
			 double mass, std::string cargotype, std::string company)
: VEHICLE(id,name,s1,s2,s3,d1,d2,d3), Mass(mass), CargoType(cargotype), Company(company) {}

TRUCK::~TRUCK()
{
	std::cout << "Zniszczono obiekt klasy TRUCK\n";
}

void TRUCK::setMass(int a)
{
	Mass=a;
}
void TRUCK::setCargoType(std::string cargotype)
{
	CargoType=cargotype;
}
void TRUCK::setCompany(std::string company)
{
	Company=company;
}
void TRUCK::show()
{
	std::cout << "Id: " << ID << " Nazwa: " << Name << '\n';
	std::cout << "Pozycja: ";
	Coords.show();
	std::cout << "Masa towaru [t]: " << Mass << '\n';
	std::cout << "Typ towaru: "+CargoType+'\n';
	std::cout << "Firma :"+Company+'\n';
}