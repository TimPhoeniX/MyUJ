#ifndef _OBJ_HPP_
#define _OBJ_HPP_
#include<vector>
#include<string>
#include<initializer_list>
#include<thread>
#include<chrono>
#include<iostream>

class POSITION
{
private:
	double Szerokosc;
	double Dlugosc;
public:
	POSITION();
	POSITION(double s1,double s2,double s3,double d1,double d2,double d3);
	POSITION(double d, double s);
	~POSITION();

	void setSzerokosc(double s1,double s2,double s3);
	void setDlugosc(double d1,double d2,double d3);
	double getSzerokosc();
	double getDlugosc();
	const double& x() const;
	const double& y() const;
	
	void change(double szerokosc, double dlugosc);
	void show();
	void add(const POSITION &p);
	void substract(const POSITION &p);
	double distance(const POSITION &a) const;
	void reverse();
	void reversey();
	void correct();
	
	POSITION operator +(const POSITION &p) const;
	POSITION operator -(const POSITION &p) const;
	POSITION& operator ++();
	POSITION& operator --();
	POSITION operator *(const double num) const;
	bool operator ==(const POSITION &p) const;
	friend std::ostream& operator<< (std::ostream& stream, const POSITION& P);
};

class VELOCITY
{
private:
	POSITION Velocity;
	double Speed;
	double Direction;
public:
	VELOCITY();
	VELOCITY(POSITION P);
	VELOCITY(double d);
	~VELOCITY();
	
	const POSITION& getVelocity() const;
	void calcSpeed();
	void setSpeed(const double speed);
	void setDirection(const double dir);
	const double& getSpeed() const;
	const double& getDirection() const;
	void change(double x, double y);
	void reverse();
	void reversey();
};

class WORLD;

class AWATAR
{
	friend class WORLD;
protected:
	POSITION Position;
	VELOCITY Velocity;
public:
	AWATAR();
	AWATAR(const POSITION& P, const POSITION& V);
	AWATAR(const POSITION& P, double d);
	~AWATAR();
	const POSITION& getPosition() const;
	const VELOCITY& getVelocity() const;
	void currentPosition();
	void movePosition(const double time);
	
};

class VICTIM;

class PREDATOR: public AWATAR
{
	friend double distance(const PREDATOR &p, const VICTIM &v);
private:
	double Visibility;
public:
	PREDATOR();
	PREDATOR(const POSITION& P, const POSITION& V);
	PREDATOR(const POSITION& P, double dir);
	~PREDATOR();
	double getVisibility() const;
};

class VICTIM: public AWATAR
{
	friend double distance(const PREDATOR &p, const VICTIM &v);
private:
	double Visibility;
public:
	VICTIM();
	VICTIM(const POSITION& P, const POSITION& V);
	VICTIM(const POSITION& P, double dir);
	~VICTIM();
	double getVisibility() const;
};

class WORLD
{
private:
	std::vector<class PREDATOR*> Predators;
	std::vector<class VICTIM*> Victims;
public:
	WORLD();
	WORLD(const unsigned int predators, const unsigned int victims);
	WORLD(std::initializer_list<PREDATOR> pred, std::initializer_list<VICTIM> vict);
	~WORLD();
	
	void addPredator();
	void addPredator(const POSITION& P, const POSITION& V);
	void addPredator(const POSITION& P, const double dir);
	void addVictim();
	void addVictim(const POSITION& P, const POSITION& V);
	void addVictim(const POSITION& P, const double dir);
	
	PREDATOR& getPredator(const unsigned int n) throw(std::string);
	VICTIM& getVictim(const unsigned int n) throw(std::string);
	
	double distance(const AWATAR &awatar1, const AWATAR &awatar2) throw(std::string);
	void redirect(PREDATOR& P, VICTIM& V);
	void simulate(const double time, const int iterations, std::ostream& stream=std::cout);
	void operator() (const double time, const int iterations, std::ostream& stream=std::cout);
//	void print() const;
};

#endif