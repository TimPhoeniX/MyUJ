#include<iostream>
using namespace std;
void fun(double *A,int size);
void fun(float *A,int size);
int main()
{
	float *tab=nullptr;
	int size = 0;
	cin >> size;
	tab=new float[size];
	delete[] tab;
	return 0;
}