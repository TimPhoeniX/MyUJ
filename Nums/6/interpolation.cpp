#include <iostream>
#include <random>
#include <chrono>
#include <functional>
#include "ctl_nci.hpp"

template class CTL::NCIFunction_CD<double>;

int main()
{
	std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> distribution(0.0,1.0);
	auto Rand = std::bind(distribution,engine);
	double* v = new double[10];
	for(int i = 0; i < 10; ++i)
	{
		v[i]=Rand();
		std::cout << "# " << v[i] << '\n';
	}
	CTL::NCIFunction_CD<double> fun(1.,1.,10,v);
	for(double i = 1.; i < 10; i+=0.0001)
	{
		std::cout << i << '\t' << fun(i) << '\n';
	}
	return 0;
}