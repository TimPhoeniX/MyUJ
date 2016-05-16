#include <iterator>
#include <iostream>

void classic_selection_sort(int t[], int n)
{
    int i, j, min;
    int temp;
    for (i = 0; i < n-1; ++i) {
        min = i;
        for (j = i+1; j < n; ++j) {
            if (t[j] < t[min]) {
                min = j;
            }
        }
        if (min != i) {
            temp = t[i];
            t[i] = t[min];
            t[min] = temp;
        }
    }
}

template <typename Iter>
void selection_sort(Iter b, Iter e)
{
    Iter i, j, min;
	typename std::iterator_traits<Iter>::value_type temp;
    for (i = b; i !=e; ++i) {
        min = i;
        for ( ++(j = i); j != e; ++j) {
            if (*j < *min) {
                min = j;
            }
        }
        if (min != i) {
            temp = *i;
            *i = *min;
            *min = temp;
        }
    }
}

int main()
{
	int arr[] {8,5,3,523,67,4};
	selection_sort(arr,arr+6);
	for(int i = 0; i < 6; ++i)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;
}