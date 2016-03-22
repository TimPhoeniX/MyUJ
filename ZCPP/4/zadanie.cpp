#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<ctime>

template <typename T, int size = 16>
class Stack
{
    T data[size];
    int top_index;

public:
    Stack() : top_index(-1)
    { }

    bool empty() const
    {
        return top_index == -1;
    }

    void push(const T & x)
    {
        data[++top_index] = x;
    }

    T & top()
    {
        return data[top_index];
    }

    const T & top() const
    {
        return data[top_index];
    }

    void pop()
    {
        top_index--;
    }
};

template<int size>
class Stack<char,size>
{
	char data[size];
    int top_index;

public:
	Stack() : top_index(-1)
    { }

    bool empty() const
    {
        return top_index == -1;
    }

    void push(const char & x)
    {
        data[++top_index] = x;
    }

    char & top()
    {
        return data[top_index];
    }

    const char & top() const
    {
        return data[top_index];
    }

    void pop()
    {
        top_index--;
    }
	
	void push(const char* string)
	{
		while(*string != 0)
		{
			this->push(*(string++));
		}
	}
};

class IsEven
{
public:
	bool operator()(int i) const
	{
		return i%2 == 0;
	}
};

int main()
{
	std::srand(std::time(0));
	IsEven e;
	std::cout << e(2) << ' ' << e(3) << std::endl;
	int* tab = new int[50];
	for(int i = 0; i < 50; ++i)
	{
		tab[i]=std::rand()%100;
	}
	std::cout << std::count_if(tab,tab+50, e) << std::endl;
	Stack<char> s;
	s.push("heya!");
	while(!s.empty())
	{
		std::cout << s.top() << std::endl;
		s.pop();
	}
	
}