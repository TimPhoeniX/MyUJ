#include "ctl_data.hpp"
#include "ctl_pair.hpp"
#include "ctl_sort.hpp"
#include <iostream>
#include <fstream>

int main()
{
	CTL::Data< CTL::Pair<int, char> > DataArray1("dane.txt");
	CTL::Data< CTL::Pair<int, char> > DataArray2(DataArray1);
	
	DataArray1.Sort(CTL::MergeSort,CTL::Pair<int,char>::LessFirst);
	DataArray1.Sort(CTL::MergeSort,CTL::Pair<int,char>::LessSecond);
	DataArray1.WriteFile("stable_sorted.txt");

	DataArray1.Sort(CTL::QuickSort,CTL::Pair<int,char>::LessFirst);
	DataArray1.Sort(CTL::QuickSort,CTL::Pair<int,char>::LessSecond);
	DataArray2.WriteFile("unstable_sorted.txt");
	
	return 0;
}