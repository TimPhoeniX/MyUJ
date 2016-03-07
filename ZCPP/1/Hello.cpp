#include<iostream>
#include<list>
#include<memory>

int main()
{
	std::allocator<float> al;
	std::list<float> ll(al);
	ll.push_back(1.1);
	ll.push_back(2.2);
	ll.push_back(3.3);
	for(auto it = ll.begin(); it!=ll.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
	std::list<float> lis(std::allocator<float>());
}

