#include <iostream>
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
	
	uj::list<int> a(t,t+10);
	uj::list<int> b(t,t+10);
	
	printer(a);
	printer(b);
	
	if(a==b) std::cout << "1OK\n";
	if(a!=b) std::cout << "2OK\n";
	if(a<b) std::cout << "3OK\n";
	
	std::cout << a==b;
	
	std::cout << a.size() << ' ' << b.size() << std::endl;
	
	return 0;
}