#include <iostream>

template <typename T>
class Register
{
private:
	T counter = 0;
public:
	void put(T val)
	{
		this->counter+=val;
	}
	
	T get()
	{
		return this->counter;
	}
	
	void reset()
	{
		this->counter=0;
	}
};

int main()
{
    Register<double> k;

    k.put(2.00);
    k.put(3.95);
    k.put(1.50);
    std::cout << k.get() << '\n';   // powinno wypisać 7.45

    k.put(2.00);
    std::cout << k.get() << '\n';   // powinno wypisać 9.45

    k.reset();
    std::cout << k.get() << '\n';   // powinno wypisać 0.0

    return 0;
}