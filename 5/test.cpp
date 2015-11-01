#include<iostream>
#include "ctl_data.hpp"

int main()
{
	CTL::Data<int> Set;
	Set.Load();
	std::cout << Set;
}