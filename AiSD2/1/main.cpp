#include "ctl_set.hpp"

template class Set<int>;

int main()
{
	AbstractSet<int>* A = new Set<int>();
	AbstractSet<int>* B = new Set<int>();
	A->Insert(1);
	A->Insert(2);
	A->Insert(3);
	B->Insert(3);
	B->Insert(4);
	B->Insert(5);
	A->Print();
	B->Print();
	auto C = A->Sum(B);
	C->Print();
	auto D = A->Difference(B);
	D->Print();
	auto E = A->Intersection(B);
	E->Print();
	A->Delete(1);
	A->Print();
	std::cout << B->IsMember(1) << ' ' << B->IsMember(5) << std::endl;
}