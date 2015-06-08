#include<iostream>
#include<iomanip>
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
	Dlugosc+=dlugosc;
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
double POSITION::distance(const POSITION &a) const
{
	return sqrt((Szerokosc-a.Szerokosc)*(Szerokosc-a.Szerokosc)+(Dlugosc-a.Dlugosc)*(Dlugosc-a.Dlugosc));
}

POSITION POSITION::operator +(const POSITION &p) const
{
	POSITION t;
	t.Szerokosc=Szerokosc+p.Szerokosc;
	t.Dlugosc=Dlugosc+p.Dlugosc;
	return t;
}
POSITION POSITION::operator -(const POSITION &p) const
{
	POSITION t;
	t.Szerokosc=Szerokosc-p.Szerokosc;
	t.Dlugosc=Dlugosc-p.Dlugosc;
	return t;
}
POSITION& POSITION::operator ++()
{
	change(0.001,0.001);
	return *this;
}
	
POSITION& POSITION::operator --()
{
	change(-0.001,-0.001);
	return *this;
}
bool POSITION::operator ==(const POSITION &p) const
{
	if(Dlugosc==p.Dlugosc && Szerokosc==p.Szerokosc)
		return true;
	else 
		return false;
}
POSITION POSITION::operator *(const double num) const
{
	POSITION temp(Dlugosc,Szerokosc);
	temp.Dlugosc*=num;
	temp.Szerokosc*=num;
	return temp;
}
std::ostream& operator<< (std::ostream& stream, const class POSITION& P)
{
	if( P.Szerokosc <= 90 && P.Szerokosc > 0)
	{
		stream << std::fixed << std::setprecision(4) << P.Szerokosc << " N ";
	}
	else if (P.Szerokosc < 0 && P.Szerokosc >= -90)
	{
		stream << std::setprecision(4) << P.Szerokosc << " S ";
	}
	else if( P.Szerokosc == 0)
	{
		stream << std::setprecision(4) << P.Szerokosc << ' ';
	}
	else stream<< "BŁĄD  ";
	if( P.Dlugosc <= 180 && P.Dlugosc >= 0)
	{
		stream << std::setprecision(4) << P.Dlugosc << " E";
	}
	else if (P.Dlugosc < 0 && P.Dlugosc >= -180)
	{
		stream << std::setprecision(4) << P.Dlugosc << " W";
	}
	else stream<< "BŁĄD";
	return stream;
}

VELOCITY::VELOCITY() : Velocity(0,0), Average(0) {}
VELOCITY::VELOCITY(double x, double y) : Velocity(y,x)
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
POSITION AWATAR::getPosition() const
{
	return Position;
}
void AWATAR::movePosition(double time)
{
	Position=Position+Velocity.getVelocity()*time;
}

PREDATOR::PREDATOR() : AWATAR(0,0,0,0), Visibility(2) {}
PREDATOR::PREDATOR(double px, double py, double vx, double vy)
: AWATAR(px, py, vx, vy), Visibility(2) {}
PREDATOR::~PREDATOR() {}
double PREDATOR::getVisibility() const
{
	return Visibility;
}

VICTIM::VICTIM() : AWATAR(0,0,0,0), Visibility(4) {}
VICTIM::VICTIM(double px, double py, double vx, double vy)
: AWATAR(px, py, vx, vy), Visibility(4) {}
VICTIM::~VICTIM() {}
double VICTIM::getVisibility() const
{
	return Visibility;
}

double distance(const PREDATOR &P, const VICTIM &V)
{
	double d=P.getPosition().distance(V.getPosition());
	if(d==0)
	{
		std::string e="Object Collision";
		throw e;
	}
	std::cout << "Odległość wynosi " << d << '\n';
	if(d<P.getVisibility())
	{
		std::cout << "Predator widzi Victim\n";
	}
	else
	{
		std::cout << "Predator nie widzi Victim\n";
	}
	if(d<V.getVisibility())
	{
		std::cout << "Victim widzi Predator\n";
	}
	else
	{
		std::cout << "Victim nie widzi Predator\n";
	}
	return d;
}

WORLD::WORLD() {}
WORLD::WORLD(std::initializer_list<PREDATOR> pred, std::initializer_list<VICTIM> vict)
{
	for(auto it: pred)
		Predators.push_back(new PREDATOR(it));
	for(auto it: vict)
		Victims.push_back(new VICTIM(it));
}
WORLD::~WORLD() 
{
	for(auto it: Predators)
		delete it;
	for(auto it: Victims)
		delete it;
}
void WORLD::addPredator()
{
	Predators.push_back(new PREDATOR);
}
void WORLD::addPredator(double px, double py, double vx, double vy)
{
	Predators.push_back(new PREDATOR(px,py,vx,vy));
}
void WORLD::addVictim()
{
	Victims.push_back(new VICTIM);
}
void WORLD::addVictim(double px, double py, double vx, double vy)
{
	Victims.push_back(new VICTIM(px,py,vx,vy));
}
PREDATOR& WORLD::getPredator(unsigned int n) throw(std::string)
{
	if(n>Predators.size())
	{
		std::string e="Not enough Predators";
		throw e;
	}
	return *Predators.at(n);
}
VICTIM& WORLD::getVictim(unsigned int n) throw(std::string)
{
	if(n>Victims.size())
	{
		std::string e="Not enough Victims";
		throw e;
	}
	return *Victims.at(n);
}

double WORLD::distance(const AWATAR &awatar1, const AWATAR &awatar2) throw(std::string)
{
	double d=awatar1.getPosition().distance(awatar2.getPosition());
// 	if(d==0)
// 	{
// 		std::string e="Object Collision";
// 		throw e;
// 	}
// 	std::cout << "Odległość wynosi " << d << '\n';
// 	if(d<P.getVisibility())
// 	{
// 		std::cout << "Predator widzi Victim\n";
// 	}
// 	else
// 	{
// 		std::cout << "Predator nie widzi Victim\n";
// 	}
// 	if(d<V.getVisibility())
// 	{
// 		std::cout << "Victim widzi Predator\n";
// 	}
// 	else
// 	{
// 		std::cout << "Victim nie widzi Predator\n";
// 	}
	return d;
}
void WORLD::simulate(double time)
{
	int tmp=10;
	while(tmp--)
	{
		for(auto p: Predators)
		{
			for(auto pbis: Predators)
			{
				if(p!=pbis)
					if(distance(*p,*pbis)==0)
						++(pbis->Position);
			}
			for(auto v: Victims)
			{
				if(distance(*p,*v)==0)
						++(v->Position);
			}
		}
		for(auto v: Victims)
		{
			for(auto vbis: Victims)
			{
				if(v!=vbis)
					if(distance(*v,*vbis)==0)
						++(vbis->Position);
			}
		}
		int i=0;
		for(auto it: Predators)
		{
			it->movePosition(time);
			std::cout << "Predator " << std::setw(5) << i++ << " position: " << it->getPosition() <<'\n';
		}
		i=0;
		for(auto it: Victims)
		{
			it->movePosition(time);
			std::cout << "Victim   " << std::setw(5) << i++ << " position: " << it->getPosition() <<'\n';
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}