#include<iostream>
#include<iomanip>
#include<random>
#include<cmath>
#include<random>
#include "obj.hpp"
#include "omp.h"

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
	correct();
}
void POSITION::add(const POSITION &p)
{
	Szerokosc+=p.Szerokosc;
	Dlugosc+=p.Dlugosc;
	correct();
}
void POSITION::substract(const POSITION &p)
{
	Szerokosc-=p.Szerokosc;
	Dlugosc-=p.Dlugosc;
	correct();
}
double POSITION::getSzerokosc()
{
	return Szerokosc;
}
double POSITION::getDlugosc()
{
	return Dlugosc;
}
const double& POSITION::x() const
{
	return Dlugosc;
}
const double& POSITION::y() const
{
	return Szerokosc;
}
double POSITION::distance(const POSITION &a) const
{
	return sqrt((Szerokosc-a.Szerokosc)*(Szerokosc-a.Szerokosc)+(Dlugosc-a.Dlugosc)*(Dlugosc-a.Dlugosc));
}

void POSITION::reverse()
{
	Dlugosc=-Dlugosc;
	Szerokosc=-Szerokosc;
}
void POSITION::reversey()
{
	Szerokosc=-Szerokosc;
}
void POSITION::correct()
{
	if(Szerokosc > 90)
	{
		while(Szerokosc >  90) Szerokosc-=180;
		Szerokosc=-Szerokosc;
		Dlugosc+=180;
	}
	if(Szerokosc < -90)
	{
		while(Szerokosc < -90) Szerokosc+=180;
		Szerokosc=-Szerokosc;
		Dlugosc+=180;
	}
	while(Dlugosc > 180) Dlugosc-=360;
	while(Dlugosc < -180) Dlugosc+=360;
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
// std::ostream& operator<< (std::ostream& stream, const POSITION& P)
// {
// 	if( P.Szerokosc <= 90 && P.Szerokosc > 0)
// 	{
// 		stream << std::fixed << std::setprecision(4) << P.Szerokosc << " N ";
// 	}
// 	else if (P.Szerokosc < 0 && P.Szerokosc >= -90)
// 	{
// 		stream << std::setprecision(4) << P.Szerokosc << " S ";
// 	}
// 	else if( P.Szerokosc == 0)
// 	{
// 		stream << std::setprecision(4) << P.Szerokosc << ' ';
// 	}
// 	else stream<< "BŁĄD  ";
// 	if( P.Dlugosc <= 180 && P.Dlugosc >= 0)
// 	{
// 		stream << std::setprecision(4) << P.Dlugosc << " E";
// 	}
// 	else if (P.Dlugosc < 0 && P.Dlugosc >= -180)
// 	{
// 		stream << std::setprecision(4) << P.Dlugosc << " W";
// 	}
// 	else stream<< "BŁĄD";
// 	return stream;
// }
std::ostream& operator<< (std::ostream& stream,const POSITION& P)
{
	stream << std::setprecision(4) << P.Dlugosc << '\t' <<std::setprecision(4) <<P.Szerokosc;
	return stream;
}

VELOCITY::VELOCITY() : Velocity(0,0), Speed(0) {}
VELOCITY::VELOCITY(POSITION P) : Velocity(P)
{
	calcSpeed();
}
VELOCITY::VELOCITY(double d) : 
	Velocity(3*cos(d),3*sin(d)), Speed(3), Direction(d) {}
VELOCITY::~VELOCITY() {}	
void VELOCITY::calcSpeed()
{
	if(Velocity.y()==0)
		Speed=Velocity.x();
	else if(Velocity.x()==0)
		Speed=Velocity.y();
	else 
		Speed=sqrt(Velocity.x()*Velocity.x()+Velocity.y()*Velocity.y());
}
const POSITION& VELOCITY::getVelocity() const
{
	return Velocity;
}
void VELOCITY::setSpeed(const double speed)
{
	Speed=speed;
	Velocity=POSITION(Speed*cos(Direction),Speed*sin(Direction));
}
void VELOCITY::setDirection(const double dir)
{
	Direction=dir;
	while(Direction<0) Direction+=2*M_PI;
	while(Direction>2*M_PI) Direction-=2*M_PI;
	Velocity=POSITION(Speed*cos(Direction),Speed*sin(Direction));
}
const double& VELOCITY::getSpeed() const
{
	return Speed;
}
const double& VELOCITY::getDirection() const
{
	return Direction;
}
void VELOCITY::change(double x, double y)
{
	Velocity.change(x,y);
}
void VELOCITY::reverse()
{
	Velocity.reverse();
}
void VELOCITY::reversey()
{
	Velocity.reversey();
}

AWATAR::AWATAR() : Position(0,0), Velocity() {}
AWATAR::AWATAR(const POSITION& P, const POSITION& V)
	: Position(P), Velocity(V) {}
AWATAR::AWATAR(const POSITION& P, double d)
	: Position(P), Velocity(d) {}
AWATAR::~AWATAR() {}

void AWATAR::currentPosition()
{
	Position=Position+Velocity.getVelocity();
	Position.show();
}
const POSITION& AWATAR::getPosition() const
{
	return Position;
}
const VELOCITY& AWATAR::getVelocity() const
{
	return Velocity;
}
void AWATAR::movePosition(const double time)
{
	Position=Position+Velocity.getVelocity()*time;
	if(Position.y() > 90 || Position.y() < -90)
	{
		Velocity.reversey();
	}
	Position.correct();
}

PREDATOR::PREDATOR() : AWATAR(), Visibility(2) {}
PREDATOR::PREDATOR(const POSITION& P, const POSITION& V)
: AWATAR(P, V), Visibility(2) {}
PREDATOR::PREDATOR(const POSITION& P, double dir)
: AWATAR(P, dir), Visibility(2) {}
PREDATOR::~PREDATOR() {}
double PREDATOR::getVisibility() const
{
	return Visibility;
}

VICTIM::VICTIM() : AWATAR(), Visibility(4) {}
VICTIM::VICTIM(const POSITION& P, const POSITION& V)
	: AWATAR(P, V), Visibility(4) {}
VICTIM::VICTIM(const POSITION& P, double dir)
	: AWATAR(P, dir), Visibility(4) {}
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
WORLD::WORLD(const unsigned int predators, const unsigned int victims)
{
	std::random_device rd;
	unsigned int seed=rd();
	std::default_random_engine DRE(seed);
	std::uniform_real_distribution<double> gx(-40,40);
	std::uniform_real_distribution<double> gy(-20,20);
	std::uniform_real_distribution<double> dir(0,2*M_PI);
	for(unsigned int i=0;i<predators;i++)
	{
		addPredator(POSITION(gx(DRE),gy(DRE)),dir(DRE));
	}
	for(unsigned int i=0;i<victims;i++)
	{
		addVictim(POSITION(gx(DRE),gy(DRE)),dir(DRE));
	}
}
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
void WORLD::addPredator(const POSITION& P, const POSITION& V)
{
	Predators.push_back(new PREDATOR(P,V));
}
void WORLD::addPredator(const POSITION& P, const double dir)
{
	Predators.push_back(new PREDATOR(P,dir));
}
void WORLD::addVictim()
{
	Victims.push_back(new VICTIM);
}
void WORLD::addVictim(const POSITION& P, const POSITION& V)
{
	Victims.push_back(new VICTIM(P,V));
}
void WORLD::addVictim(const POSITION& P, const double dir)
{
	Victims.push_back(new VICTIM(P,dir));
}
PREDATOR& WORLD::getPredator(const unsigned int n) throw(std::string)
{
	if(n>Predators.size())
	{
		std::string e="Not enough Predators";
		throw e;
	}
	return *Predators.at(n);
}
VICTIM& WORLD::getVictim(const unsigned int n) throw(std::string)
{
	if(n>Victims.size())
	{
		std::string e="Not enough Victims";
		throw e;
	}
	return *Victims.at(n);
}

void WORLD::redirect(PREDATOR& P, VICTIM& V)
{
	auto VPos=V.Position-P.Position;
	auto Pdir=P.Velocity.getDirection();
	auto y=VPos.x()*sin(-Pdir)+VPos.y()*cos(-Pdir);
	if(y>0)
		V.Velocity.setDirection(Pdir+(M_PI/2));
	else if(y<0)
		V.Velocity.setDirection(Pdir-(M_PI/2));
}

double WORLD::distance(const AWATAR &awatar1, const AWATAR &awatar2) throw(std::string)
{
	return awatar1.getPosition().distance(awatar2.getPosition());
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
}

// #pragma GCC push_options
// #pragma GCC optimize("O3")
// void WORLD::simulate(double time)
// {
// 	int tmp=10;
// 	while(tmp--)
// 	{
// //#pragma omp parallel for default(shared) private(p,pbis,v,d) num_threads(4)
// 		for(auto p: Predators)
// 		{
// 			for(auto pbis: Predators)
// 			{
// 				if(p!=pbis)
// 					if(distance(*p,*pbis)==0)
// 						++(pbis->Position);
// 			}
// 			for(auto v: Victims)
// 			{
// 				double d;
// 				if((d=distance(*p,*v))==0)
// 				{
// 						++(v->Position);
// 				}
// 				if(d<v->getVisibility())
// 				{
// 					v->Velocity.reverse();
// 				}
// 			}
// 		}
// 		for(auto v: Victims)
// 		{
// 			for(auto vbis: Victims)
// 			{
// 				if(v!=vbis)
// 					if(distance(*v,*vbis)==0)
// 						++(vbis->Position);
// 			}
// 		}
// 		int i=0;
// 		for(auto it: Predators)
// 		{
// 			it->movePosition(time);
// 			std::cout << "Predator " << std::setw(5) << i++ << " position: " << it->getPosition() <<'\n';
// 		}
// 		i=0;
// 		for(auto it: Victims)
// 		{
// 			it->movePosition(time);
// 			std::cout << "Victim   " << std::setw(5) << i++ << " position: " << it->getPosition() <<'\n';
// 		}
// 		std::this_thread::sleep_for(std::chrono::seconds(1));
// 	}
// }
// #pragma GCC pop_options

#pragma GCC push_options
#pragma GCC optimize("O3")
void WORLD::simulate(const double time, const int iterations,std::ostream& stream)
{
	int countdown=iterations;
	while(countdown--)
	{
//#pragma omp parallel for default(shared) private(p,pbis,v,d) num_threads(4)
		for(auto p: Predators)
		{
// 			for(auto pbis: Predators)
// 			{
// 				if(p!=pbis)
// 					if(distance(*p,*pbis)==0)
// 						++(pbis->Position);
// 			}
			int i=0;
			for(auto v: Victims)
			{
				i++;
				double d=distance(*p,*v);
// 				if((d=distance(*p,*v))==0)
// 				{
// 						++(v->Position);
// 				}
				if(d<v->getVisibility())
				{
//					v->Velocity.reverse();
					if(abs(abs(p->Velocity.getDirection()-v->Velocity.getDirection())-M_PI/2)>0.01)
					{
//						std::cout << i <<"!\n";
						redirect(*p,*v);
					}
				}
			}
		}
// 		for(auto v: Victims)
// 		{
// 			for(auto vbis: Victims)
// 			{
// 				if(v!=vbis)
// 					if(distance(*v,*vbis)==0)
// 						++(vbis->Position);
// 			}
// 		}
		stream << iterations-countdown << '\t';
		for(auto it: Predators)
		{
			it->movePosition(time);
			stream << it->getPosition() <<'\t';
		}
//		i=0;
		for(auto it: Victims)
		{
			it->movePosition(time);
			stream << it->getPosition() <<'\t';
		}
		stream << '\n';
//		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
#pragma GCC pop_options