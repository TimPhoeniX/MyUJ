#include<iostream>
#include "Miasto.hpp"

using namespace std;

int main()
{
	Miasto A("Kraków", 555555, 10, 20 ,20, 30, 40 ,50);
	A.pokaz();
	A.zmiennazwe("Radomyśl");
	A.zmienludnosc(1000);
	A.zmienpolozenie(-53, -35, -10, -20, -40, -50);
	A.pokaz();
}