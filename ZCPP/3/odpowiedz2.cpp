#include <string>
#include <iostream>
#include <set>
#include <fstream>

int main()
{
	std::set<std::string> Words;
	std::string input = "";
	std::ifstream Stream("words.txt");
	while(!Stream.eof())
	{
		Stream >> input;
		Words.emplace(input);
	}
	for(const std::string& w: Words)
	{
		std::cout << w << std::endl;
	}
}