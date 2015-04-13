#include <iostream>
using namespace std;

void tree(int line)
{
	int i,space,k=0;
	for(i=1;i<=line;++i) 
	{
		for(space=1;space<=line-i;++space) 
		{
			cout<<" ";
		} 
		while(k!=2*i-1)
		{
			cout<<"*";
			++k;
		}
		k=0;
		cout<<"\n";
	} 
}

void tree(int line, int x)

int main()
{
	tree(3);
	return 0;
}