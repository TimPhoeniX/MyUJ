#include <iostream>
#include <cstdlib>

int* CreateArray(int ArraySize)
{
    int* Array=new int[ArraySize];
    for(int i=0;i<ArraySize;++i)
    {
        std::cin >> Array[i];
    }
    return Array;
}

void PrintArray(int* Array, int ArraySize)
{
	for(int i = 0; i < ArraySize; ++i)
	{
		std::cout << Array[i] << " ";
	}
	std::cout << std::endl;
}

bool Ascending(int a, int b)
{
	return a>b;
}

bool Descending(int a, int b)
{
	return a<b;
}

void InsertionSort(int* A, int size, bool(*compare)(int,int))
{
	for(int j = 1; j < size; ++j)
	{
		int key=A[j];
		int i=j-1;
		while( i>=0 && compare(A[i],key))
		{
			A[i+1]=A[i];
			i=i-1;
		}
		A[i+1]=key;
	}
}

int main(int argc, char* argv[])
{
	bool (*Compare)(int,int) = nullptr;
	void (*Sort)(int*, int, bool (*)(int,int)) = nullptr;
	int SetNum = 0, SetSize = 0, *Set = nullptr;
	if(argc < 3)
	{
		std::cerr << "Not enough arguments\n";
		return -1;
	}
	switch(atoi(argv[1]))
	{
		case 1:
			//bubble sort
			break;
		case 2:
			Sort = InsertionSort;
			break;
		case 3: 
			//merge sort
			break;
		default:
			std::cerr << "First argument invalid\n";
			return -1;
	}
	switch(atoi(argv[2]))
	{
		case 0:
			Compare = Ascending;
			break;
		case 1:
			Compare = Descending;
			break;
		default:
			std::cerr << "Second argument invalid\n";
			return -1;
	}
	std::cin >> SetNum;
	for(int i = 0; i < SetNum; ++i)
	{
		std::cin >> SetSize;
		Set = CreateArray(SetSize);
		Sort(Set,SetSize,Compare);
		PrintArray(Set,SetSize);
	}
	return 0;
}