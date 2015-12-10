#include <string>
#include <sstream>
#include "ctl_open_map.hpp"
#include <iostream>
#include <cstdlib>

class Hasher
{
public:
	virtual ~Hasher()
	{
	}
	
	virtual unsigned int operator()(const std::string& str) const
	{
		unsigned int hash = 0;
		for(char i : str)
		{
			hash=hash*12809+i; //12809
		}
		return hash;
	}
	virtual unsigned int operator()(const std::string& str, unsigned int it) const = 0;
	
// 	virtual unsigned int operator()(const std::string& str, unsigned int it) const
// 	{
// 		return this->operator()(str);
// 	}
};

class LinearHasher : public Hasher
{
public:
	unsigned int operator()(const std::string& str, unsigned int it) const
	{
		return this->Hasher::operator()(str)+it;
	}
};

class QuadraticHasher : public Hasher
{
public:
	unsigned int operator()(const std::string& str, unsigned int it) const
	{
		return this->Hasher::operator()(str)+it+it*it;
	}
};

class DoubleHasher : public Hasher
{
private:
	std::hash<std::string> Secondary = decltype(Secondary)();
public:
	unsigned int operator()(const std::string& str, unsigned int it) const
	{
		return this->Hasher::operator()(str)+it*Secondary(str);
	}
};

class HasherWrapper //Decent enough
{
private:
	Hasher* Hash = nullptr;
public:
	HasherWrapper(Hasher* h)
	: Hash(h)
	{
	}
	
	HasherWrapper(HasherWrapper&& w)
	: Hash(w.Hash)
	{
		w.Hash=nullptr;
	}
	
	~HasherWrapper()
	{
		delete this->Hash;
	}
	
	unsigned int operator()(const std::string& str, unsigned int it)
	{
		return this->Hash->operator()(str,it);
	}
};

HasherWrapper HasherFactory(int i)
{
	switch(i)
	{
		case 0:
			return new LinearHasher();
			break;
		case 1:
			return new QuadraticHasher();
			break;
		case 2:
			return new DoubleHasher();
			break;
		default:
			return nullptr;
	}
}

int main(int argc, char** argv)
{
	if(argc!=3)
	{
		std::cerr << "Expected 2 arguments\n";
		return -1;
	}
	unsigned int Size = std::atoi(argv[1]);
	CTL::OpenMap<std::string,std::string,HasherWrapper> Map(Size,HasherFactory(std::atoi(argv[2])) );
	std::string Surname, Name;
	unsigned int Count = 0;
	while(std::cin >> Surname && Surname.length() > 0)
	{
		std::cin >> Name;
		Count+=Map.Insert(Surname,Name);
	}
	std::cout << Count << std::endl;
	return 0;
}