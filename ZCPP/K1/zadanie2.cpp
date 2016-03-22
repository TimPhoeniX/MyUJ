#include <iostream>

template <typename T, int N = 16>
class Stack
{
private:
    T _rep[N];
    int _top;

public:
    Stack() : _top(0) {
    }

    void push(T x) {
        _rep[_top++] = x;
    }

    T pop() {
        return _rep[--_top];
    }

    bool empty() {
        return _top == 0;
    }

    int size()
	{
		return this->_top;
	}
};

template<typename T, typename StackType>
class PositiveStackAdapter
{
private:
	StackType s;
public:
	void push(T x)
	{
		if(x > 0) s.push(x);
	}
	
	T pop() {
        return s.pop();
    }

    bool empty() {
        return s.empty();
    }

    int size()
	{
		return s.size();
	}
};

int main()
{
    PositiveStackAdapter< int, Stack<int> > a;

    a.push(7);
    a.push(-13);
    a.push(2);
    while (! a.empty()) {
        std::cout << a.pop() << '\n';
    }                   // powinno wypisać 2 7

    return 0;
}