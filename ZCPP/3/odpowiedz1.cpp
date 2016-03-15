#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

int main()
{
	std::vector<int> Liczby;
	int input = -1;
	std::cin >> input;
	while(input!=0)
	{
		Liczby.push_back(input);
		std::cin >> input;
	}
	int min = std::numeric_limits<int>::max();
	int max = std::numeric_limits<int>::min();
	for(std::vector<int>::iterator it = Liczby.begin(), end = Liczby.end(); it!=end; ++it)
	{
		if(*it < min) min = *it;
		if(*it > max) max = *it;		
	}
	std::cout << "MIN: " << min << " MAX: " << max << std::endl;
	
	auto mm = minmax_element(Liczby.begin(), Liczby.end());
	
	std::cout << "MIN: " << *min_element(Liczby.begin(), Liczby.end()) << " MAX: " << *max_element(Liczby.begin(), Liczby.end()) << std::endl;
	
	std::cout << "MIN: " << *mm.first << " MAX: " << *mm.second << std::endl;
}

//W C++98 były vector, deque, list, set, multiset, map, multimap, stack, queue, priority_queue
//W C++11 dodano array, forward_list, unorderer_set, unorderer_multiset, unorderer_map, unorderer_multimap 