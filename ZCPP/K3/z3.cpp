#include <iterator>

template<typename Iter, typename T>
bool Search(Iter a, Iter b, T& x, std::random_access_iterator_tag)
{
	Iter c = a;
	while(a < b)
	{
		c = a + (b - a) / 2;
		if(x < *c) b = c;
		else if(x > *c) a = c + 1;
		else return true;
	}
	return false;
}

template<typename Iter, typename T>
bool Search(Iter a, Iter b, T& x, std::input_iterator_tag)
{
	while(a!=b && !(*a > x))
	{
		if(*(a++) == x) return true;
	}
	return false;
}

template<typename Iter, typename T>
bool search_in_sorted_sequence(Iter a, Iter b, T x)
{
	return Search(a, b, x, typename std::iterator_traits<Iter>::iterator_category() );
}

#include <iostream>
#include <vector>
#include <list>

int main()
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	std::vector<int>vec;
	vec.push_back(1);
	vec.push_back(4);
	vec.push_back(7);
	vec.push_back(9);
	std::list<int>lst;
	lst.push_back
		(3);
	lst.push_back(4);
	lst.push_back(6);
	lst.push_back(7);
	std::cout << std::boolalpha;    // print booleans as "true"/"false"
	std::cout << search_in_sorted_sequence(arr, arr + 5, 1)
		<< '\n';    // should print "true"
		std::cout << search_in_sorted_sequence(vec.begin(), vec.end(), 5)
		<< '\n';    // should print "false"
		std::cout << search_in_sorted_sequence(lst.begin(), lst.end(), 7)
		<< '\n';    // should print "true"
		return 0;
}