#ifndef _MIASTO_HPP_
#define _MIASTO_HPP_
class Miasto
{
	private:
		std::string nazwa;
		unsigned int ludnosc;
		double szerokosc;
		double dlugosc;
		
	public:
		Miasto();
		Miasto(std::string name, int people, double s1, double s2 ,double s3 ,double d1,double d2 ,double d3);
		~Miasto();
		void zmiennazwe(std::string name);
		void zmienludnosc(int people);
		void zmienpolozenie(double s1, double s2 ,double s3 ,double d1,double d2 ,double d3);
		void pokaz();
};
#endif // _MIASTO_HPP_