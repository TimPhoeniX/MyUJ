#include "ctl_data.hpp"
#include "ctl_pair.hpp"
#include "ctl_sort.hpp"
#include <iostream>
#include <fstream>

int main()
{
	std::ifstream DataFile("dane.txt");
	CTL::Data< CTL::Pair<int, char> > DataArray1(DataFile);
	CTL::Data< CTL::Pair<int, char> > DataArray2(DataArray1);
	DataFile.close();
	CTL::MergeSort(DataArray1.begin(),DataArray1.end(),
		[](CTL::Pair<int, char> lhs, CTL::Pair<int, char> rhs)->bool
		{
			return lhs.GetFirst()<rhs.GetFirst();
		});
	CTL::MergeSort(DataArray1.begin(),DataArray1.end(),
		[](CTL::Pair<int, char> lhs, CTL::Pair<int, char> rhs)->bool
		{
			return lhs.GetSecond()<rhs.GetSecond();
		});
	std::ofstream StableSorted("stable_sorted.txt");
	StableSorted << DataArray1; StableSorted.close();
	CTL::QuickSort(DataArray2.begin(),DataArray2.end(),
		[](CTL::Pair<int, char> lhs, CTL::Pair<int, char> rhs)->bool
		{
			return lhs.GetFirst()<rhs.GetFirst();
		});
	CTL::QuickSort(DataArray2.begin(),DataArray2.end(),
		[](CTL::Pair<int, char> lhs, CTL::Pair<int, char> rhs)->bool
		{
			return lhs.GetSecond()<rhs.GetSecond();
		});
	std::ofstream UnstableSorted("unstable_sorted.txt");
	UnstableSorted << DataArray2; UnstableSorted.close();
	return 0;
}