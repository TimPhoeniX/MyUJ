#include "ctl_matrix.hpp"
#include <fstream>
#include <iostream>

int main()
{
	std::cout << "Enter square matrix dimension, please: ";
	int dim = 0;
	std::cin >> dim;
	CTL::Matrix<double> m(dim,dim);
	std::cout << "Enter matrix elements by starting with first row, from left to right, please: " << std::endl;
	m.FillWith(std::cin);
	unsigned int* permutationVector = new unsigned int[dim];
	m.InplaceLU(permutationVector);
	auto mm = m.ReassembleFromLU();
	std::cout << "Restored A:\n" << mm.InplaceReversePermutateRows(permutationVector);
}