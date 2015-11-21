#include "ctl_matrix.hpp"
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream File("matrices.txt");
	for(int i = 0; i < 3; ++i)
	{
		CTL::Matrix<double> m1(File);
		CTL::Matrix<double> m2(File);
		m1.QRAlgorithmSymmetricalTridiagonal();
		m2.TridiagonalizeSymmetricHouseholder();
		m2.QRAlgorithmSymmetricalTridiagonal();
		m1.PrintDiagonal(); std::cout << std::endl;
		m2.PrintDiagonal(); std::cout << std::endl;
	}
	File.close();return 0;
}