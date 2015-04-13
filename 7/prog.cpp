#include<iostream>
#include "Vehicles.hpp"

int main()
{
	class VEHICLE *v1=nullptr;
	class VEHICLE *v2=nullptr;
	v1=new BUS(12,"Pojazd A",50,03,0,19,57,0,30,1,"Adam","Kowalski");
	v1->show();
	v2 = new TRUCK(66,"Pojazd B",52,14,0,21,0,0,28.5,"latwopalny","Kurier");
	v2->show();
	delete v1;
	delete v2;
}