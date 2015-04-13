#include<iostream>

int silnia(int n)
{
	if(n<0) return 0;
	else if(n==0) return 1;
	else
	{
		int S=n*silnia(n-1);
		return S;
	}
}

int main()
{
	std::cout << silnia(8)<< std::endl;
}