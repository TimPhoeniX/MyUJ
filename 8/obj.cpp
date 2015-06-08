#include<iostream>
#include<iomanip>
#include<string>
#include<random>
#include<cmath>
#include "obj.hpp"

POSITION::POSITION() : Szerokosc(0), Dlugosc(0) {}; 
POSITION::POSITION(double s1,double s2,double s3,double d1,double d2,double d3)
: Szerokosc(s1+s2/60+s3/3600), Dlugosc(d1+d2/60+d3/3600)
{
	if( Szerokosc > 90 || Szerokosc < -90 )

		std::cout << " BLAD ";
	if (Dlugosc > 180 || Dlugosc < -180 )

		std::cout << " BLAD ";
}
POSITION::POSITION(double d, double s): Szerokosc(s), Dlugosc(d) {}
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
void POSITION::change(double szerokosc, double dlugosc)
{
	Szerokosc+=szerokosc;
	dlugosc+=dlugosc;
//	if(Szerokosc > 90)
//	else if (Szerokosc < -90 )
	while(Dlugosc > 180)
		Dlugosc-=360;
	while(Dlugosc < -180)
		Dlugosc+=360;
}
void POSITION::add(const POSITION &p)
{
	Szerokosc+=p.Szerokosc;
	Dlugosc+=p.Dlugosc;
	while(Dlugosc > 180)
		Dlugosc-=360;
	while(Dlugosc < -180)
		Dlugosc+=360;
}
void POSITION::substract(const POSITION &p)
{
	Szerokosc-=p.Szerokosc;
	Dlugosc-=p.Dlugosc;
	while(Dlugosc > 180)
		Dlugosc-=360;
	while(Dlugosc < -180)
		Dlugosc+=360;
}
double POSITION::getSzerokosc()
{
	return Szerokosc;
}
double POSITION::getDlugosc()
{
	return Dlugosc;
}

POSITION POSITION::operator +(const POSITION &p)
{
	POSITION t;
	t.Szerokosc=Szerokosc+p.Szerokosc;
	t.Dlugosc=Dlugosc+p.Dlugosc;
	return t;
}
POSITION POSITION::operator -(const POSITION &p)
{
	POSITION t;
	t.Szerokosc=Szerokosc-p.Szerokosc;
	t.Dlugosc=Dlugosc-p.Dlugosc;
	return t;
}
POSITION& POSITION::operator ++()
{
	change(0.01,0.01);
	return *this;
}
	
POSITION& POSITION::operator --()
{
	change(-0.01,-0.01);
	return *this;
}
bool POSITION::operator ==(const POSITION &p)
{
	if(Dlugosc==p.Dlugosc && Szerokosc==p.Szerokosc)
		return true;
	else 
		return false;
}

VELOCITY::VELOCITY() : Velocity(0,0), Average(0) {}
VELOCITY::VELOCITY(double x, double y) : Velocity(x,y)
{
	calcAverage();
}
VELOCITY::~VELOCITY() {}	
void VELOCITY::calcAverage()
{
	if(Velocity.getSzerokosc()==0)
		Average=Velocity.getDlugosc();
	else if(Velocity.getDlugosc()==0)
		Average=Velocity.getSzerokosc();
	else 
		Average=sqrt(Velocity.getDlugosc()*Velocity.getDlugosc()+Velocity.getSzerokosc()*Velocity.getSzerokosc());
}
POSITION VELOCITY::getVelocity()
{
	return Velocity;
}
void VELOCITY::change(double x, double y)
{
	Velocity.change(x,y);
}

AWATAR::AWATAR() : Position(0,0), Velocity(0,0) {}
AWATAR::AWATAR(double px, double py, double vx, double vy)
: Position(px,py), Velocity(vx, vy) {}
AWATAR::~AWATAR() {}

void AWATAR::currentPosition()
{
	Position=Position+Velocity.getVelocity();
	Position.show();
}
