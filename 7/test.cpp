#include "ctl_arraylist.hpp"
#include "ctl_forwardlist.hpp"
#include "ctl_linkedlist.hpp"
#include "test.hpp"

#include <iostream>
#include <initializer_list>

int main()
{
	TestList<CTL::ArrayList,int>();
	return 0;
}
