#include "ctl_stack.hpp"
#include "test.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

int main()
{
	AssertStack();
	CTL::Stack<char> Operators;
	CTL::Stack<int> Priority;
	int val = 0;
	int c = 0;
	std::string Exp = "";
	std::stringstream Stream;
	while(std::getline(std::cin,Exp) && !Exp.empty())
	{
		Stream.clear();
		Stream.str(Exp);
		while(!Stream.eof())
		{
			c = Stream.get();
			switch(c)
			{
				case '+':
				case '-':
					while( !Operators.Empty() && Priority.Top() >= 1)
					{
						Priority.Pop();
						std::cout << Operators.Pop() << ' ';
					}
					Priority.Push(1);
					Operators.Push(c);
					break;
				case '*':
				case '/':
					while( !Operators.Empty() && Priority.Top() >= 2)
					{
						Priority.Pop();
						std::cout << Operators.Pop() << ' ';
					}
					Priority.Push(2);
					Operators.Push(c);
					break;
				case '~':
					while( !Operators.Empty() && Priority.Top() >= 3)
					{
						Priority.Pop();
						std::cout << Operators.Pop() << ' ';
					}
					Priority.Push(3);
					Operators.Push(c);
					break;
				case '^':
					while( !Operators.Empty() && Priority.Top() >= 4)
					{
						Priority.Pop();
						std::cout << Operators.Pop() << ' ';
					}
					Priority.Push(4);
					Operators.Push(c);
					break;
				case '(':
					Operators.Push(c);
					Priority.Push(0);
					break;
				case ')':
					Priority.Pop();
					c = Operators.Pop();
					while(c != '(' )
					{
						std::cout << char(c) << ' ';
						Priority.Pop();
						c = Operators.Pop();
					}
					break;
				case '0': case '1': case '2': case '3':
				case '4': case '5': case '6': case '7':
				case '8': case '9': // Why can't 0 ... 9 be a part of the standard ?!
					Stream.unget();
					Stream >> val;
					std::cout << val << ' ';
					break;
				default: 
					break;
			}
		}
		while(!Operators.Empty())
		{
			Priority.Pop();
			std::cout << Operators.Pop() << ' ';
		}
		std::cout << std::endl;
	}
	return 0;
}