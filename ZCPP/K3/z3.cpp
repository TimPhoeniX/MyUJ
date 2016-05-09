#include <iterator>

template<typename Iter, typename T>
//bool Search(Iter a, Iter b, T& x, std::random_access_iterator_tag
bool BSearch(Iter a, Iter b, const T& x)
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
//bool Search(Iter a, Iter b, T& x, std::input_iterator_tag)
bool LSearch(Iter a, Iter b,const T& x)
{
	while(a!=b && !(*a > x))
	{
		if(*(a++) == x) return true;
	}
	return false;
}

template<bool B, typename Iter, typename T>
struct conditional
{
	static bool(*const search)(Iter,Iter,const T&);
};
template<bool B, typename Iter, typename T>
bool(*const conditional<B,Iter,T>::search)(Iter, Iter, const T&) = &LSearch<Iter, T>;

template<typename Iter, typename T>
struct conditional<true,Iter,T>
{
	static bool(*const search)(Iter, Iter, const T&);
};
template<typename Iter, typename T>
bool(*const conditional<true, Iter, T>::search)(Iter, Iter, const T&) = &BSearch<Iter, T>;

template<typename Iter, typename T>
bool search_in_sorted_sequence(Iter a, Iter b, T x)
{
	//return Search(a, b, x, typename std::iterator_traits<Iter>::iterator_category() );
	return conditional<std::is_base_of<std::random_access_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>::value, Iter, T>::search(a, b, x);
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