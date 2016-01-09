#include <cmath>
#include <iostream>
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
	CTL::Matrix<double> vec(2,1,new double[2]{1,11});
	CTL::Matrix<double> j(2,2);
	CTL::Matrix<double> next(2,1);
	unsigned int* p = new unsigned int[2];
	for(int i = 0; i < 100; ++i)
	{
		std::cout << i << '\n';
		next=G(vec);
		J(j,vec);
		std::cout << j;
		std::cout << next;
		j.InplaceLU(p);
		next.InplacePermutateRows(p);
		std::cout << j;
		std::cout << next;
		next=j.SolveWithLU(next);
		std::cout << next;
//		next.InplaceReversePermutateRows(p);
		vec=vec-next;
	}
	std::cout << vec << std::endl;
	return 0;
}
