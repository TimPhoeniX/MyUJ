#include <iostream>
#include "ctl_bst.hpp"
#include <random>

template class CTL::BSTNode<int>;
template class CTL::BSTInorderIterator<int>;
template class CTL::BSTree<int>;

int main()
{
	CTL::BSTree<int> tree;
	char c = 0;
	int val= 0;
	bool Working =- true;
	while(Working)
	{
		std::cin >> c;
		switch(c)
		{
			case 'w':
				std::cin >> val;
				tree.Insert(val);
				break;
			case 'u':
				std::cin >> val;
				tree.Delete(tree.Find(val));
				break;
			case 'M':
				std::cout << tree.Maximum();
				std::cout << '\n';
				break;
			case 'm':
				std::cout << tree.Minimum();
				std::cout << '\n';
				break;
			case 'i':
				tree.InorderPrint(std::cout);
				break;
			case 'R':
				tree.RestoreWithPreorder(std::cin);
				break;
			case 'r':
				tree.PreorderPrint(std::cout);
				break;
			case 'O':
				tree.RestoreWithPostorder(std::cin);
				break;
			case 'o':
				tree.PostorderPrint(std::cout);
				break;
			case 'q':
				Working=false;
				break;
			default:
				break;
		}
	}
}
