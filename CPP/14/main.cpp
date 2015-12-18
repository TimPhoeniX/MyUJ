//#define private public
#include "obj.hpp"
#include "octree.hpp"
#include<fstream>


int main()
{
	{
		WORLD X(3,10);
		std::ofstream fplot("plot.txt");
		X.simulate(0.5,200,fplot);
	}
}