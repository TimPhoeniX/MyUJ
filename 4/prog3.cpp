#include<iostream>
#include<string>

using namespace std;

struct pudlo
{
	string producent;
	float wysokosc;
	float szerokosc;
	float dlugosc;
	float objetosc;
};

template<typename AnyType>
void create(AnyType** arr,int size)
{
	(*arr) = new AnyType[size];
}

template<typename AnyType>
void destroy(AnyType** arr)
{
	delete[] (*arr);
	(*arr)=nullptr;
}

template<typename AnyType>
void fill(AnyType** arr, int size)
{
	for(int i=0;i<size;i++)
	{
		cout << "Podaj: ";
		cin >> (*arr)[i];
	}
}
void fill(struct pudlo **arr, int size)
{
	for(int i=0;i<size;i++)
	{
		cout << "Podaj producent: ";
		cin >> (*arr)[i].producent;
		cout << "Podaj wysokosc: ";
		cin >> (*arr)[i].wysokosc;
		cout << "Podaj szerokosc: ";
		cin >> (*arr)[i].szerokosc;
		cout << "Podaj dlugosc: ";
		cin >> (*arr)[i].dlugosc;
		cout << "Podaj objetosc: ";
		cin >> (*arr)[i].objetosc;
	}
}

template<typename AnyType>
void show(AnyType* arr, int size)
{
	for(int i=0;i<size;i++)
	{
		cout << arr[i] << endl;;
	}
}

void show(struct pudlo *arr, int size)
{
	for(int i=0;i<size;i++)
	{
		cout << "producent: " << arr->producent << '\n';
		cout << "wysokosc: " << arr[i].wysokosc << '\n';
		cout << "szerokosc: " << arr[i].szerokosc << '\n';
		cout << "dlugosc: " << arr[i].dlugosc << '\n';
		cout << "objetosc: "<< arr[i].objetosc << '\n';
	}
}


int main()
{
	
	int *INT=nullptr, sint=4;
	float *FLOAT=nullptr, sfloat=4;
	struct pudlo *BOX=nullptr;
	
	create(&INT,sint);
	fill(&INT,sint);
	show(INT,sint);
	destroy(&INT);
	
	create(&FLOAT,sfloat);
	fill(&FLOAT,sfloat);
	show(FLOAT,sfloat);
	destroy(&FLOAT);
	
	create(&BOX,2);
	fill(&BOX,2);
	show(BOX,2);
	destroy(&BOX);
	
	return 0;
}