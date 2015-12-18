#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <random>
#include <functional>
#include <chrono>

constexpr int Tries()
{
	return 100000000;
}

double ProbabilityDensity(double x)
{
	if(-1 <= x && x < 0)
		return (1./3.*x+1./3.);
	else if(0 <= x && x < 2)
		return (1./3.);
	else if(2 <= x && x <= 3)
		return (-1./3.*x+1);
	else return 0.;
}

double TrapezoidDistribution(double y)
{
	if(0 <= y && y < 1./6.)
		return (sqrt(6.*y)-1);
	else if( 1./6. <= y && y < 5./6.)
		return ( (6.*y-1.)/2. );
	else if( 5./6. <= y && y <= 1)
		return (3.-sqrt(6.-6.*y));
	else return 0;
}

int main()
{
	std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> distribution(0.0,1.0);
//	std::uniform_real_distribution<double> testing(-1.,3.);
	auto Throw = std::bind(distribution,engine);
//	auto Test = std::bind(testing,engine);
	double* Histogram = new double[4000] {0};
	double Var = 0;
	for(int i = 0; i < Tries(); ++i)
	{
//		Var = Test();
		Var = TrapezoidDistribution(Throw());
		++Histogram[int(floor(1000.*Var))+1000];
	}
	for(int i = 0; i < 4000; ++i)
		Histogram[i]/=(Tries()*0.001);
	std::ofstream file("data.txt");
	file.precision(6);
	for(int i = 0; i < 4000; ++i)
		file << (i-1000)/1000. << '\t' <<std::fixed << Histogram[i] << '\t' << std::fixed << ProbabilityDensity((i-1000)/1000.) << '\n';
	file.close();
	return 0;
}