#ifndef _OBJ_HPP_
#define _OBJ_HPP_

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
	
	POSITION operator +(const POSITION &p);
	POSITION operator -(const POSITION &p);
	POSITION& operator ++();
	POSITION& operator --();
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

class AWATAR
{
private:
	POSITION Position;
	VELOCITY Velocity;
public:
	AWATAR();
	AWATAR(double px, double py, double vx, double vy);
	~AWATAR();
	
	void currentPosition();
};
#endif