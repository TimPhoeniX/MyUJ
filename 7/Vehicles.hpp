#ifndef _VEHICLES_HPP_
#define _VEHICLES_HPP_
class POSITION
{
	private:
		double Szerokosc;
		double Dlugosc;
	public:
		POSITION();
		POSITION(double s1,double s2,double s3,double d1,double d2,double d3);
		~POSITION();

		void setSzerokosc(double s1,double s2,double s3);
		void setDlugosc(double d1,double d2,double d3);

		void show();
};

class VEHICLE
{
	private:
		static unsigned int Count;
	protected:
		unsigned int ID;
		std::string Name;
		POSITION Coords;
	public:
		VEHICLE();
		VEHICLE(unsigned int id, std::string name, double s1,double s2,double s3,double d1,double d2,double d3);
		virtual ~VEHICLE();

		void setCoords(double s1,double s2,double s3,double d1,double d2,double d3);
		void setName(std::string name);
		void setID(unsigned int id);

		virtual void show();
		static void incCount();
		static void decCount();
};

class BUS : public VEHICLE
{
	private:
		unsigned int Passangers;
		unsigned int Drivers;
		std::string DriverName;
		std::string DriverSurname;
	public:
		BUS();
		BUS(unsigned int id,std::string name,double s1,double s2,double s3,double d1,double d2,double d3,
			unsigned int passangers, unsigned int drivers, std::string drivername, std::string driversurname);
		~BUS();
		
		void setPassangers(int a);
		void setDrivers(int a);
		void setDriverName(std::string drivername);
		void setDriverSurname(std::string driversurname);
		
		void show();
};

class TRUCK : public VEHICLE
{
	private:
		double Mass;
		std::string CargoType;
		std::string Company;
	
	public:
		TRUCK();
		TRUCK(unsigned int id, std::string name, double s1,double s2,double s3,double d1,double d2,double d3,
			  double mass, std::string cargotype, std::string company);
		~TRUCK();

		void setMass(int a);
		void setCargoType(std::string cargotype);
		void setCompany(std::string company);
		
		void show();
};
#endif