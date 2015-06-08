#include "obj.hpp"
#include<iostream>
#include<unistd.h>

int main()
{
	AWATAR Obj(-5,5,-1,1);
	for(int i=0; i<1000; ++i)
	{
		Obj.currentPosition();
		sleep(1);
	}
}