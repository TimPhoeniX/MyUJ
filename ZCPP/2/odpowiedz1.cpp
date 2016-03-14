#include <iostream>

template <typename T>
T sum_of_array_elements(T * begin, T * end)
{
    T suma;
	while(begin!=end)
	{
		suma+=*(begin++);
	}
	return suma;
}

int main()
{
	int A[] = {1,2,3,4};
	std::cout << sum_of_array_elements(A,A+4) << std::endl;
}