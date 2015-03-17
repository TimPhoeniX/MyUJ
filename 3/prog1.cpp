#include<iostream>
#include<random>

using namespace std;

int create(double **array, int size_of_array)
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
}

int show(double *array, int size_of_array)
{
	for(int i=0; i<size_of_array; i++)
	{
		cout << array[i] << '\n';
	}
}

int destroy(double **array)
{
	delete[] (*array);
}
int main(int argc, char* argv[])
{
	double *tab =nullptr;
	int size_of_tab;
	if(argc > 1) size_of_tab = atoi(argv[1]);
	else
	{
		cout << "Podaj rozmiar: ";
		cin >> size_of_tab;
	}
	create(&tab,size_of_tab);
	show(tab,size_of_tab);
	destroy(&tab);
	return 0;
}