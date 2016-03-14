#include <iostream>
#include "Stos.h"

template<typename T, typename StackType>
class DoublingStack
{
private:
	StackType base;
public:
	DoublingStack()
	{
	}
	
	bool empty() const
    {
        return base.empty();
    }

    void push(const T & x)
    {
        base.push(x);
		base.push(x);
    }

    T & top()
    {
        return base.top();
    }

    const T & top() const
    {
        return base.top();
    }

    void pop()
    {
        base.pop();
    }
};

int main()
{
    Stack_module_1_exercise_4<int> a;

    a.push(1); a.push(2); a.push(3);
    while (! a.empty()) {
        std::cout << a.top() << '\n';
        a.pop();
    }                   // powinno wypisać 3 2 1

    DoublingStack< int, Stack_module_1_exercise_4<int> > b;

    b.push(1); b.push(2); b.push(3);
    while (! b.empty()) {
        std::cout << b.top() << '\n';
        b.pop();
    }                   // powinno wypisać 3 3 2 2 1 1

    return 0;
}