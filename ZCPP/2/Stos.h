#ifndef _ZMPWCPP_STOS_H
#define _ZMPWCPP_STOS_H

template <typename T, int size = 16>
class Stack_module_1_exercise_4
{
    T data[size];
    int top_index;

public:
    Stack_module_1_exercise_4() : top_index(-1)
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

#endif
