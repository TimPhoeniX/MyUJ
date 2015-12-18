#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <chrono>
#include <functional>
#include <map>

double PoissonProbability( const unsigned int k, const double lambda )
{
	return ( std::pow(lambda,k)*std::exp(-lambda)/std::tgamma(k+1) );
}

unsigned int PoissonDistribution( const double u, const double lambda )
{
	double q = std::exp(-lambda), s = q, p=q;
	unsigned int k = 0;
	while( u > s )
	{
		++k;
		p=p*lambda/double(k);
		s+=p;
	}
	return k;
}

constexpr unsigned int Tries()
{
	return 100000000;
}

int main()
{
	std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> distribution(0.0,1.0);
	auto Throw = std::bind(distribution,engine);
	auto PoissonP = std::bind(PoissonProbability, std::placeholders::_1, 4);
	auto PoissonD = std::bind(PoissonDistribution,Throw,4);
	std::map<unsigned int,double> Histogram;
	for(unsigned int i = 0; i < Tries(); ++i)
	{
		++Histogram[PoissonD()];
	}
	for(auto& h : Histogram)
	{
		h.second/=double(Tries());
	}
	std::ofstream results("results.txt");
	results.precision(16);
	results << std::fixed;
	for(auto h : Histogram)
	{
		results << h.first << '\t' << h.second << '\t' << PoissonP(h.first) << '\n';
	}
	results.close();
	return 0;
}