#include <utility>
#include <iostream>

void printSort(int* A, int n)
{
	for(int i = 0; i < n; ++i)
	{
		std::cout << A[i] << " ";
	}
	std::cout << std::endl;
}

void bubbleSort(int* A, int n)
{
	for(int i = 0; i < n; ++i)
	{
		for(int j = n-1; j > i; --j)
		{
			if(A[j] < A[j-1])
			{
				std::swap(A[j],A[j-1]);
	//			printSort(A,n);
			}
			
		}
	}
}

int findMin(int* A, int a, int b)
{
	int min = A[a];
	int minindex = a;
	for(int i = a; i < b; ++i)
	{
		if(A[i]<min)
		{
			min=A[i];
			minindex=i;
		}
	}
	return minindex;
}

void selectionsort(int* A, int n)
{
	for(int i = 0; i < n; ++i)
	{
		int minindex=findMin(A,i,n);
		{
			std::swap(A[i],A[minindex]);
		}
//		printSort(A,10);
	}
}

int main()
{
	int A[] = {9,5,3,4,6,7,8,1,0,2};
	bubbleSort(A,10);
	printSort(A,10);
	return 0;
}