#include <iostream>

template <typename T, int N = 100>
class Stack {
    T _rep[N];
    int _top;
public:
    class iterator {
        T* it = nullptr;
	public:
		iterator(T* p) : it(p){}
	
		T& operator*()
		{
			return *it;
		}
		
		iterator& operator++()
		{
			--it;
			return *this;
		}
		
		bool operator!=(const iterator& t)
		{
			return it!=t.it;
		}
    };
	
	Stack(): _top(0){}
	
	bool empty()
	{
		return _top == 0;
	}
	
	iterator begin()
	{
		return iterator(_rep+(_top-1));
	}
	
	iterator end()
	{
		return iterator(_rep-1);
	}
	
	void push(const T& e)
	{
		_rep[_top++] = e;
	}
	
	T pop()
	{
		return _rep[--_top];
	}
	
    // *** tu wpisz swój kod ***
};

int main()
{
    Stack<double> s;

    s.push(1);
    s.push(2.5);
    s.push(3.3);

    // powinno wypisać 3.3 2.5 1
    for (Stack<double>::iterator it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    return 0;
}