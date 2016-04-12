#include <iostream>
#include "z1.hpp"
#include <forward_list>
#include <typeinfo>

int main()
{
	double* tab = new double[10]{1.,2.,3.,4.,5.,6.,7.,-8.,0.,9.};
	std::forward_list<int> l(tab,tab+10);
	std::cout << find_min(tab,tab) << std::endl << find_min(tab,tab+10) << std::endl;
	std::cout << find_min(l.begin(),l.begin()) << std::endl << find_min(l.begin(),l.end()) << std::endl;
	                    
	std::cout << typeid(long).name() << std::endl;
}