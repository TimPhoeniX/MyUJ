#ifndef min_finder_hpp
#define min_finder_hpp

#include <iterator>
#include <type_traits>
#include <limits>

template<typename FIterator>
auto find_min(FIterator begin, FIterator end) // -std=c++14 !
//typename std::iterator_traits<FIterator>::value_type find_min(FIterator begin, FIterator end) // -std=c++11
{
	using value = typename std::iterator_traits<FIterator>::value_type;
	static_assert(std::numeric_limits<value>::is_specialized,"Cannot recognize the type");
	static_assert(std::is_base_of<std::forward_iterator_tag,typename std::iterator_traits<FIterator>::iterator_category>::value,"Cannot find min in given range");
	if(begin==end) return std::numeric_limits<value>::lowest();
	value min = std::numeric_limits<value>::max();
	while(begin!=end)
	{
		if(*begin < min) min = *begin;
		++begin;
	}
	return min;
}

#endif