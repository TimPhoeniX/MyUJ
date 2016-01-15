#include <chrono>
#include <random>
#include <cmath>
#include <iostream>
#include <functional>

double MonteCarloVolume(unsigned int dim, const unsigned int rolls = 10000000u)
{
	double distance = 0;
	std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> distrib(-0.5,0.5);
	auto Roll = std::bind(distrib,engine);
	unsigned int hits = 0;
	for(unsigned int i = 0; i < rolls; ++i)
	{
		distance = 0;
		for(unsigned int r = 0; r < dim; ++r)
		{
			distance+=std::pow(Roll(),2);
		}
		if(distance<=0.25) ++hits;
	}
	return (hits*1.)/rolls;
}

double Volume(unsigned int dim)
{
	return (std::pow(M_PI,dim*0.5)*std::pow(0.5,dim))/std::tgamma(dim*0.5+1);
}

int main()
{
	std::cout.width(10);
	std::cout.precision(10);
	std::cout.setf(std::ios::fixed);
	for(unsigned int r = 1000u; r < 1000000000u; r*=10)
	{
		std::cout << "Number of rolls: " << r << std::endl;
		for(int i = 1; i < 11; ++i)
		{
			double MC = MonteCarloVolume(i,r);
			double A = Volume(i);
			double diff = std::abs(A-MC);
			std::cout << "MC: " << MC << " Analitic: " << A << " Absolute Difference: " << diff << std::endl;
		}
		std::cout << std::endl;
	}
	return 0;
}