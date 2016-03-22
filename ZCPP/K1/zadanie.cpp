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

int main()
{
    Stack<char> c;

    std::cout << c.size() << '\n';      // powinno wypisać 0
    c.push('a');
    c.push('b');
    c.push('c');
    std::cout << c.size() << '\n';      // powinno wypisać 3

    return 0;
}

