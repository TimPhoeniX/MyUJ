#include "ctl_arraylist.hpp"
#include "ctl_forwardlist.hpp"
#include "ctl_linkedlist.hpp"
#include "test.hpp"

#include <iostream>
#include <initializer_list>

int main()
{
	std::cout << "Testing: ArrayList" << std::endl;
	TestList<CTL::ArrayList,int>();
	std::cout << "Tested:  ArrayList - Succes" << std::endl;
	
	std::cout << "Testing: ForwardList" << std::endl;
	TestList<CTL::ForwardList,int>();
	std::cout << "Tested:  ForwardList - Succes" << std::endl;
	
	std::cout << "Testing: LinkedList" << std::endl;
	TestList<CTL::LinkedList,int>();
	std::cout << "Tested:  LinkedList - Succes" << std::endl;
	
	return 0;
}
