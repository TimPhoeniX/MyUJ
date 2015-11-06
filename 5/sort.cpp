#include "ctl_data.hpp"
#include "ctl_pair.hpp"
#include "ctl_sort.hpp"
#include <iostream>
#include <fstream>

int main()
{
	std::ifstream DataFile("dane.txt");
	std::ofstream ResultFile("wyniki.txt");
	typedef typename CTL::Pair<int,char> Para;
	for(int i = 0; i < 3; ++i)
	{
		CTL::Data<Para> DataArray1(DataFile);
		CTL::Data<Para> DataArray2(DataArray1);
		
		ResultFile << "Dane    : " <<DataArray1 << std::endl;
		
		if(i!=2)
		{
			DataArray1.Sort(CTL::MergeSort,Para::LessFirst);
			DataArray2.Sort(CTL::QuickSort,Para::LessFirst);
		}
		
		if(i!=1)
		{
			DataArray1.Sort(CTL::MergeSort,Para::LessSecond);
			DataArray2.Sort(CTL::QuickSort,Para::LessSecond);
		}
		
		ResultFile << "Stable  : " << DataArray1 << std::endl \
			<< "Unstable: " << DataArray2 << std::endl << std::endl;
	}
	DataFile.close();
	ResultFile.close();
	return 0;
}