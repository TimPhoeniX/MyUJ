#define private public
#include "obj.hpp"
#include "octree.hpp"
#include "octree.cpp"


int main()
{
	Octree::OCTREE<POSITION> Tree;
	Tree.addMore(19);
	Tree.print();
	Tree.printNode(69);
	Octree::ONodeIt<POSITION> check;
	if(Tree.Root->findIDIt(3,check)) (*check)->printNode();
	Tree.removeNode(18);
	if(Tree.Root->findIDIt(18,check)) (*check)->printNode();
	Tree.removeNode(55);
}