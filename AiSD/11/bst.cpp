#include <iostream>
#include "ctl_bst.hpp"
#include <random>

template class CTL::BSTNode<int>;
template class CTL::BSTInorderIterator<int>;
template class CTL::BSTree<int>;

int main()
{
	CTL::BSTree<int> tree;
	std::default_random_engine engine(45223);
	std::uniform_int_distribution<int> dist(-10,111);
	auto random = std::bind(dist,engine);
	for(int i = 0; i < 20; ++i)
	{
		auto s = random();
		std::cout << s << ' ';
		tree.Insert(s);
	}
	std::cout << std::endl;
	for(auto it: tree)
	{
		std::cout << it << std::endl;
	}
	return 0;
}
