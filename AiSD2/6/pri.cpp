#include <iostream>
#include <queue>
#include <random>
#include <functional>

std::default_random_engine en;
std::uniform_int_distribution<> dist(0,100);
auto rnd = std::bind(dist,en);

class Test
{
public:
	int val = 0;
	
	void randomize(int value)
	{
		val = rnd()+value;
	}
};

int main()
{
	Test* arr = new Test[10];
	for(int i = 0; i < 10; ++i)
	{
		arr[i].randomize(0);
	}
	
	std::priority_queue<Test*,std::vector<Test*>,std::function<bool(Test*,Test*)>> q([](Test* a, Test* b)->bool{return a->val < b->val;});
	
	for(int i = 0; i < 10; ++i)
	{
		q.push(arr+1);
	}
	
	while(!q.empty())
	{
		int val = q.top()->val;
		std::cout << val << ' ';
		for(int i = 0; i < 10; ++i)
		{
			arr[i].randomize(val);
		}
		q.pop();
	}
	std::cout << std::endl;
	delete[] arr;
	return 0;
}