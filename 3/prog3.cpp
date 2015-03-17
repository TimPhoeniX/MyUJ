#include<iostream>
#include<random>

using namespace std;

int main(int argc,char* argv[])
{
	double *tab =nullptr;
	int size_of_tab;
	if(argc > 1) size_of_tab = atoi(argv[1]);
	else
	{
		cout << "Podaj rozmiar: ";
		cin >> size_of_tab;
	}
	auto lamba_fun1 = [](double** array,int size_of_array) -> int
	{
		if((*array)!=nullptr) return 1;
		(*array) = new double[size_of_array];
		default_random_engine engine;
		uniform_real_distribution<double> generator_lf(-100,100);
		for(int i=0; i<size_of_array; i++)
		{
			(*array)[i]=generator_lf(engine);
		}
	return 0;
	};
	auto lamba_fun2 = [](double *array, int size_of_array) ->int
	{
		for(int i=0; i<size_of_array; i++)
		{
			cout << array[i] << '\n';
		}
	};
	auto lamba_fun3 = [](double **array)->int { delete[] (*array); };
	lamba_fun1(&tab,size_of_tab);
	lamba_fun2(tab,size_of_tab);
	lamba_fun3(&tab);
	[](){}();
	return 0;
}