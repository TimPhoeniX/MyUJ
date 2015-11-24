#include "ctl_stack.hpp"
#include "test.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

int main()
{
	AssertStack();
	CTL::Stack<int> Int;
	CTL::Stack<int> Priority;
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
				case '-':
					b = Int.Pop();
					sb = Expressions.Pop();
					if(Priority.Pop() <= 1) sb='('+sb+')';
					a = Int.Pop();
					sa = Expressions.Pop();
					if(Priority.Pop() < 1) sa='('+sa+')';
					Int.Push( c=='+'? a+b : a-b );
					Expressions.Push(sa+char(c)+sb);
					Priority.Push(1);
					break;
				case '*':
				case '/':
					b = Int.Pop();
					sb = Expressions.Pop();
					if(Priority.Pop() <= 2) sb='('+sb+')';
					a = Int.Pop();
					sa = Expressions.Pop();
					if(Priority.Pop() < 2) sa='('+sa+')';;
					Int.Push( c=='*'? a*b : a/b );
					Expressions.Push(sa+char(c)+sb);
					Priority.Push(2);
					break;
				case '~':
					a = Int.Pop();
					sa = Expressions.Pop();
					if(Priority.Pop() <= 3) sb='('+sb+')';
					Int.Push(-a);
					Expressions.Push('~'+sa);
					Priority.Push(3);
					break;
				case '^':
					b = Int.Pop();
					sb = Expressions.Pop();
					if(Priority.Pop() <= 4) sb='('+sb+')';
					a = Int.Pop();
					sa = Expressions.Pop();
					if(Priority.Pop() < 4) sa='('+sa+')';
					Int.Push(std::pow(a,b));
					Expressions.Push(sa+'^'+sb);
					Priority.Push(4);
					break;
				default:
					Stream.unget();
					Stream >> val;
					Int.Push(val);
					Expressions.Push(std::to_string(val));
					Priority.Push(5);
					break;
			}
		}
		Priority.Pop();
		std::cout << Int.Pop() << '\n' << Expressions.Pop() << std::endl;
	}
	
	return 0;
}