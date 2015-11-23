#include "ctl_stack.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

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
		int val = 0;
		int b = 0;
		int a = 0;
		std::string sb = "";
		std::string sa = "";
		while(!Stream.eof())
		{
			auto c = Stream.get();
			switch(c)
			{
				case ' ':
				case -1: 
					break;
				case '+':
					b = Int.Pop();
					a = Int.Pop();
					sb = Expressions.Pop();
					sa = Expressions.Pop();
					Int.Push(a+b);
					Expressions.Push('('+sa+'+'+sb+')');
					break;
				case '-':
					b = Int.Pop();
					a = Int.Pop();
					sb = Expressions.Pop();
					sa = Expressions.Pop();
					Int.Push(a-b);
					Expressions.Push('('+sa+'-'+sb+')');
					break;
				case '*':
					b = Int.Pop();
					a = Int.Pop();
					sb = Expressions.Pop();
					sa = Expressions.Pop();
					Int.Push(a*b);
					Expressions.Push(sa+'*'+sb);
					break;
				case '/':
					b = Int.Pop();
					a = Int.Pop();
					sb = Expressions.Pop();
					sa = Expressions.Pop();
					Int.Push(a/b);
					Expressions.Push(sa+'/'+sb);
					break;
				case '^':
					b = Int.Pop();
					a = Int.Pop();
					sb = Expressions.Pop();
					sa = Expressions.Pop();
					Int.Push(std::pow(a,b));
					Expressions.Push('('+sa+")^("+sb+')');
					break;
				case '~':
					a = Int.Pop();
					sa = Expressions.Pop();
					Int.Push(-a);
					Expressions.Push("(-"+sa+')');
					break;
				default:
					Stream.unget();
					Stream >> val;
					Int.Push(val);
					Expressions.Push(std::to_string(val));
					break;
			}
		}
		std::cout << Int.Pop() << '\n' << Expressions.Pop() << std::endl;
	}
	
	return 0;
}