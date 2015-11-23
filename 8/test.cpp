#include "ctl_stack.hpp"
#include <iostream>
#include <string>
#include <sstream>



int main()
{
	CTL::Stack<int> Int;
	CTL::Stack<std::string> Expressions;
	std::string Exp;
	std::stringstream Stream;
	while(std::getline(std::cin,Exp) && !Exp.empty())
	{
		Stream.str(Exp);
		Stream.clear();
		while(!Stream.eof())
		{
			auto c = Stream.get();
			std::cout << c << std::endl;
			switch(c)
			{
				case ' ': break;
			}
		}
	}
	
	return 0;
}