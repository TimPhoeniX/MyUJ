#include <cmath>
#include <iostream>
#include <vector>
#include "ctl_matrix.hpp"

CTL::Matrix<double> G(const CTL::Matrix<double>& vec)
{
	auto x = vec[0][0];
	auto y = vec[1][0];
	return CTL::Matrix<double>(2,1,new double[2]
	{ 2*y*y+x*x-2, (x-1)*(x-1)+(y-0.5)*(y-0.5)-0.25 });
}

CTL::Matrix<double>& J(CTL::Matrix<double>& j, const CTL::Matrix<double>& vec)
{
	auto x = vec[0][0];
	auto y = vec[1][0];
	j[0][0]=( 2*x );
	j[0][1]=( 4*y );
	j[1][0]=( (x-1)*2 );
	j[1][1]=( 2*y-1 );
	return j;
}

int main()
{
	std::vector<CTL::Matrix<double>> results;
	unsigned int* p = new unsigned int[2];
	for(double a = -250.; a < 250.1; a+=0.25)
	{
		for(double b = -250.; b < 250.1; b+=0.25)
		{
			unsigned int limit = 1000000;
			CTL::Matrix<double> vec(2,1,new double[2]{a,b});
			CTL::Matrix<double> j(2,2);
			CTL::Matrix<double> next = G(vec);
			while(!next.ConvergenceToZero() && --limit)
			{
				next=G(vec);
				J(j,vec);
				j.InplaceLU(p);
				next.InplacePermutateRows(p);
				next=j.SolveWithLU(next);
				vec=vec-next;
			}
			if([&]()->bool
				{
					for(auto& i : results)
					{
						if( (i-vec).ConvergenceToZero(8) ) return false;
					}
					return true; 
				}()) results.push_back(vec);
		}
	}
	delete[] p;
	for(auto& i : results)
	{
		std::cout << "Solution:\n" << i << std::endl;
	}
	return 0;
}
