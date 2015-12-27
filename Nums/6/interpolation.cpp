#include <cmath>
#include <iostream>
#include "ctl_nci.hpp"

template class CTL::NCIFunction_CD<double>;

int main()
{
	double* v = new double[10] {0.1,0.3,0.2,0.5,0.4,0.6,0.7,0.5,0.8,0.6};
	CTL::NCIFunction_CD<double> fun(1.,1.,10,v);
	for(double i = 1.; i < 10; i+=0.001)
	{
		std::cout << i << '\t' << fun(i) << '\n';
	}
	return 0;
}