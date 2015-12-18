#include "ctl_proto_hashmap.hpp"
#include "test.hpp"
#include <string>
#include <sstream>
#include <fstream>

class Hasher
{
public:
	unsigned int operator()(const std::string& str)
	{
		unsigned int hash = 0;
		for(char i : str)
		{
			hash=hash*12809+i; //12809
		}
		return hash;
	}
};

int main(int argc, char** argv)
{
	std::ios_base::sync_with_stdio(false);
	if(argc != 2)
	{
		return -1;
	}
	else if(*argv[1] == 't')
	{
		AssertMap();
	}
	else if(*argv[1] == 'm')
	{
		int size = 0;
		std::cin >> size;
		std::cin.get();
		CTL::UnorderedMapPrototype<std::string,std::string,std::equal_to<std::string>,Hasher> map;
		std::string surname;
		std::string name;
		std::string line;
		std::stringstream stream;
		for(int i = 0; i < size; ++i)
		{
			stream.clear();
			std::getline(std::cin,line);
			stream.str(line);
			std::getline(stream,surname,' ');
			while(stream.get() == ' ');
			stream.unget();
			std::getline(stream,name);
			map.Insert(surname,name);
		}
		std::cout << map.getMaxListLen() << ' '  << map.getMedianListLen() << std::endl;
	}
}