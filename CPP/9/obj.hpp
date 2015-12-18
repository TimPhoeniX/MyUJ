#ifndef _OBJ_HPP_
#define _OBJ_HPP_
#include<vector>
#include<string>

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
	
	POSITION operator +(const POSITION &p) const;
	POSITION operator -(const POSITION &p) const;
	POSITION& operator ++();
	POSITION& operator --();
	POSITION operator*(const int t) const;
	bool operator ==(const POSITION &p);
	
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
	const POSITION& getPosition() const;
	void currentPosition();
	
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
	~WORLD();
	
	void addPredator();
	void addPredator(double px, double py, double vx, double vy);
	void addVictim();
	void addVictim(double px, double py, double vx, double vy);
	
	PREDATOR& getPredator(unsigned int n) throw(std::string);
	VICTIM& getVictim(unsigned int n) throw(std::string);
	
	double distance(const PREDATOR &p, const VICTIM &v) throw(std::string);
	double distance(const AWATAR &A, const AWATAR &B) const throw(std::string);
};

#endif