#include <iostream>
#include <random>
#include <cmath>

int main()
{
	std::random_device rd;
	std::default_random_engine Randomizer(rd());
	std::uniform_real_distribution<double> Distrib(0, 1);
	for( int N = 10; N <= 10000000; N*=10)
	{
		int Hits = 0;
		for(int i = 0; i < N; ++i)
		{
			double a = Distrib(rd);
			double b = Distrib(rd);
			if(sqrt(a*a+b*b) <= 1) ++Hits;
		}
		std::cout << "Losowań: " << N << " pi: " << (4.*Hits/N) << '\n';
	}
	return 0;
}