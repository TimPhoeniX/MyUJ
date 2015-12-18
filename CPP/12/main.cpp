#define private public
#include "obj.hpp"
#include "octree.hpp"


int main()
{
	{
		PREDATOR p(0,0,1,1);
		VICTIM v(2,2,-1,-1);
		WORLD X({p,p,p},{v,v,v});
		X.simulate(1);
	//	X.~WORLD();
	}
	Octree::OCTREE<POSITION> Tree;
	Tree.addMore(19,POSITION(15,15));
	Tree.print();
	Tree.printNode(69);	
	try{ std::cout << Tree.setVal(5,POSITION(5,5)) << '\n';}
	catch(const std::exception& exc) {std::cout << "Exception: " << exc.what() << '\n';}
	try{ std::cout << Tree.getVal(20) << '\n';}
	catch(const std::exception& exc) {std::cout << "Exception: " << exc.what() << '\n';}
}