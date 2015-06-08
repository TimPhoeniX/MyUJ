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
	
	void change(double szerokosc, double dlugosc);
	void show();
	void add(const POSITION &p);
	void substract(const POSITION &p);
	double distance(const POSITION &a) const;
	void reverse();
	void correct();
	
	POSITION operator +(const POSITION &p) const;
	POSITION operator -(const POSITION &p) const;
	POSITION& operator ++();
	POSITION& operator --();
	POSITION operator *(const double num) const;
	bool operator ==(const POSITION &p) const;
	friend std::ostream& operator<< (std::ostream& stream, const class POSITION& P);
};

class VELOCITY
{
private:
	POSITION Velocity;
	double Average;
public:
	VELOCITY();
	VELOCITY(double x, double y);
	~VELOCITY();
	
	POSITION getVelocity();
	void calcAverage();
	void change(double x, double y);
	void reverse();
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
	AWATAR(double px, double py, double vx, double vy);
	~AWATAR();
	POSITION getPosition() const;
	void currentPosition();
	void movePosition(double time);
	
};

class VICTIM;

class PREDATOR: public AWATAR
{
	friend double distance(const PREDATOR &p, const VICTIM &v);
private:
	double Visibility;
public:
	PREDATOR();
	PREDATOR(double px, double py, double vx, double vy);
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
	VICTIM(double px, double py, double vx, double vy);
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
	void addPredator(const double px, const double py, const double vx, const double vy);
	void addVictim();
	void addVictim(const double px, const double py, const double vx, const double vy);
	
	PREDATOR& getPredator(const unsigned int n) throw(std::string);
	VICTIM& getVictim(const unsigned int n) throw(std::string);
	
	double distance(const AWATAR &awatar1, const AWATAR &awatar2) throw(std::string);
	void simulate(const double time, const int iterations, std::ostream& stream=std::cout);
//	void print() const;
};

#endif