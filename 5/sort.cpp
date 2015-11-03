#include "ctl_data.hpp"
#include "ctl_pair.hpp"
#include <iostream>
#include <fstream>

int main()
{
	std::ifstream DataFile("dane.txt");
	CTL::Data< CTL::Pair<int, char> > DataArray(DataFile);
	DataFile.close();
	std::cout << DataArray << std::endl;
	CTL::Pair<int, char> a(1,'A'), b(2,'B');
	std::swap(a,b);
	std::cout << a << ' ' << b;
	return 0;
}