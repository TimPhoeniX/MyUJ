#include <iostream>
#include <list>
#include "uj_list.hpp"

template class uj::list<int>;

template<typename container>
void printer(const container& c)
{
	for(auto& it : c)
	{
		std::cout << it << ' ';
	}
	std::cout << std::endl;
}

int main()
{
	int* t = new int[10] {0,1,2,3,4,5,6,7,8,9};
	
	uj::list<int> a(t,t+9);
	uj::list<int> b(t,t+9);
	
	printer(a);
	printer(b);
	
	std::cout << (a==b) << ' ' << (a!=b) << ' ' << (a<b) << ' ' << (a<=b) << ' ' << (a>b) << ' ' << (a>=b) << ' ' << std::endl;
	
	std::cout << a.size() << ' ' << b.size() << std::endl;
	
	return 0;
}