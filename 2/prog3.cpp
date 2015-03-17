#include<iostream>
#include<array>
#include<vector>
#include<string>
#include<list>
using namespace std;

struct BATONIK 
{
	string nazwa;
	double masa;
	int liczba_kalorii;
};

int dodajBatonik(list<struct BATONIK>& lista)
{
	struct BATONIK temp;
	cout << "Podaj nazwę: ";
	cin >> temp.nazwa;
	cout << "Podaj masę: ";
	cin >> temp.masa;
	cout << "Podaj liczbę kalorii: ";
	cin >> temp.liczba_kalorii;
	lista.push_back(temp);
	return 0;
}
int wyswietlBatoniki(list<struct BATONIK> lista)
{
	for(list<struct BATONIK>::iterator it= lista.begin();it!=lista.end();++it)
		cout << "nazwa=" << (*it).nazwa << " masa=" << (*it).masa << " kalorie=" << (*it).liczba_kalorii<< '\n';
	for(auto it: lista)
		cout << "nazwa=" << it.nazwa << " masa=" << it.masa << " kalorie=" << it.liczba_kalorii<< '\n';
	return 0;
}
int main(void)
{
	double *tab=new double[10];
	array<double,10> arr ={{0,0,0,0,0,0,0,0,0,0}};
	vector<double> vec(10);
	cout << tab[0] <<" | "<< arr[0] <<" | "<< vec[0] <<endl;
	cout << tab[0] <<" | "<< arr.at(0) <<" | "<< vec.at(0) <<endl;
	delete[] tab;
	int add=0;
	for(auto &it: arr)
	{
		it=+(add++);
		cout << ' ' << it;
	}
	cout << '\n';
	for(auto &it: vec)
	{
		cout << ' ' << it;
	}
	cout << '\n';

	list<struct BATONIK> lis;
	dodajBatonik(lis);
	dodajBatonik(lis);
	wyswietlBatoniki(lis);
	return 0;
}