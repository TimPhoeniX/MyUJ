#include<vector>
#include<list>
#include<array>
#include<map>
#include<queue>
#include<iostream>
#include<algorithm>
#include "obj.hpp"
using namespace std;

int main()
{
	vector<class POSITION*> vec;
	vec.push_back(new POSITION(3,4));
	vec.push_back(new POSITION(2,6));
	vec.push_back(new POSITION(1,5));
	vec.insert(vec.begin()+1,new POSITION(0,0));
	cout << "Stan początkowy vectora\n";
	for(auto it: vec)
	{
		it->show();
	}
	sort(vec.begin(),vec.end(),[](class POSITION* a , class POSITION* b)->bool{return a->getDlugosc()<b->getDlugosc();});
	cout << "Sort po długości\n";
	for(auto it: vec)
	{
		it->show();
	}
	sort(vec.begin(),vec.end(),[](class POSITION* a , class POSITION* b)->bool{return a->getSzerokosc()<b->getSzerokosc();});
	cout << "Sort po szerokości\n";
	for(auto it: vec)
	{
		it->show();
	}
	for(auto it: vec)
	{
		delete it;
	}
	list<class POSITION*> lis;
	lis.push_back(new POSITION(3,4));
	lis.push_back(new POSITION(2,6));
	lis.push_back(new POSITION(1,5));
	cout << "Stan początkowy listy\n";
	for(auto it: lis)
	{
		it->show();
	}
	lis.sort([](class POSITION* a , class POSITION* b)->bool{return a->getDlugosc()<b->getDlugosc();});
	cout << "Sort po długości\n";
	for(auto it: lis)
	{
		it->show();
	}
	lis.sort([](class POSITION* a , class POSITION* b)->bool{return a->getSzerokosc()<b->getSzerokosc();});
	cout << "Sort po szerokości\n";
	for(auto it: lis)
	{
		it->show();
	}
	for(auto it: lis)
	{
		delete it;
	}
	array<class POSITION*,3> arr;
	arr.at(0)=new POSITION(3,4);
	arr.at(1)=new POSITION(2,6);
	arr.at(2)=new POSITION(1,5);
	cout << "Stan początkowy arraya\n";
	for(auto it: arr)
	{
		it->show();
	}
	sort(arr.begin(),arr.end(),[](class POSITION* a , class POSITION* b)->bool{return a->getDlugosc()<b->getDlugosc();});
	cout << "Sort po długości\n";
	for(auto it: arr)
	{
		it->show();
	}
	sort(arr.begin(),arr.end(),[](class POSITION* a , class POSITION* b)->bool{return a->getSzerokosc()<b->getSzerokosc();});
	cout << "Sort po szerokości\n";
	for(auto it: arr)
	{
		it->show();
	}
	for(auto it: arr)
	{
		delete it;
	}
	queue<class POSITION*> que;
	que.push(new POSITION(3,4));
	que.push(new POSITION(2,6));
	que.push(new POSITION(1,5));
	cout << "Stan kolejki (Nie do posortowanie)\n";
	for(unsigned int i= 0;i<3;++i)
	{
		que.front()->show();
		delete que.front();
		que.pop();
	}
	map<unsigned int,class POSITION*> ma1;
	ma1.insert(pair<unsigned int,class POSITION*>(3,new POSITION(3,4)));
	ma1.insert(pair<unsigned int,class POSITION*>(2,new POSITION(2,6)));
	ma1.insert(pair<unsigned int,class POSITION*>(1,new POSITION(1,5)));
	cout << "Stan mapy (Automatycznie sortowane wg. zadanego klucza)\n";
	for(auto it: ma1)
	{
		cout << it.first << ". ";
		it.second->show();
	}
	multimap<unsigned int,class POSITION*,bool(*)(unsigned int a, unsigned int b)> mm([](unsigned int a, unsigned int b)->bool{return a>b;});
	mm.insert(pair<unsigned int,class POSITION*>(1,new POSITION(3,4)));
	mm.insert(pair<unsigned int,class POSITION*>(3,new POSITION(2,6)));
	mm.insert(pair<unsigned int,class POSITION*>(2,new POSITION(1,5)));
	cout << "Stan multimapy (Automatycznie sortowane wg. zadanego klucza)\n";
	for(auto it: mm)
	{
		cout << it.first << ". ";
		cout << *it.second << '\n';
	}
	auto it = mm.begin();
	cout << it->first << ". " << *(it->second) << '\n';
}
// 	multimap<unsigned int, class POSITION* > mma;