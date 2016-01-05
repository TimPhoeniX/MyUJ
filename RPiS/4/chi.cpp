#include <random>
#include <chrono>
#include <cmath>
#include <map>
#include <functional>
#include <fstream>
#include <iostream>

double ChiSquare(const unsigned int n, double x)
{
//	return std::pow(x*0.5,n*0.5-1)*std::exp(-x*0.5)*0.5/std::tgamma(n*0.5);
	if(x==1.) std::cerr << std::pow(x/2.,n/2.-1.) << ' ' << std::exp(-x/2) << ' ' << std::tgamma(n/2.) << '\n'; 
	return std::pow(x/2.,n/2.-1.)*std::exp(-x/2)/2./std::tgamma(n/2.);
//	return std::pow(x,n*0.5-1)*std::exp(-x*0.5)*0.5/(std::pow(2,n/2.)*std::tgamma(n*0.5));
}

template<typename RealType = double>
class BoxMuller
{	
public:
	template<typename UniformRNG>
	RealType operator()(UniformRNG& u)
	{
		return std::sqrt(-2*std::log(u()))*std::cos(2*M_PI*u());
	}
};

constexpr int Tries()
{
	return 10000000;
}

template<typename RealType = double>
class ChiSquaredDistribution
{
private:
	unsigned int Param = 0;
public:
	ChiSquaredDistribution(unsigned int n)
	: Param(n)
	{
	}
	
	template<typename NormalDistribution>
	RealType operator()(NormalDistribution& d)
	{
		RealType var = 0;
		RealType norm = 0;
		for(unsigned int i = 0; i < this->Param; ++i)
		{
			norm = d();
			var+=(norm*norm);
		}
		return var;
	}
};


int main()
{
	std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> distribution(0.0,1.0);
	auto Throw = std::bind(distribution,engine);
	BoxMuller<> Normal;
	auto Norm = std::bind(Normal,std::ref(Throw));
	ChiSquaredDistribution<> Chi(3);
	auto Chi3 = std::bind(Chi,std::ref(Norm));
	std::map<unsigned int,double> Histogram;
	double Var = 0;
	for(int i = 0; i < Tries(); ++i)
	{
		Var = Chi3();
		++Histogram[int(floor(1000.*Var))];
	}
	for(auto& h : Histogram)
	{
		h.second/=(double(Tries())*0.001);
	}
	std::ofstream results("results.txt");
	results.precision(16);
	results << std::fixed;
	for(auto h : Histogram)
	{
		results << h.first*0.001 << '\t' << h.second << '\t' << ChiSquare(3,h.first*0.001) << '\n';
	}
	results.close();
	return 0;
}