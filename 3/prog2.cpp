#include<iostream>

using namespace std;

void print1()
{
	cout << "Hello\n";
}

void print2()
{
	cout << "World\n";
}

void print3()
{
	cout << "!\n";
}

int main()
{
	void (*print)() = nullptr;
	for(int i=0; i<10; i++)
	{
		if((i%3)==0) print=print1;
		else if((i%3)==1) print=print2;
		else if((i%3)==2) print=print3;
		print();
	}
	return 0;
}