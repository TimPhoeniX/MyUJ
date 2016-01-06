#include <cmath>
#include <iostream>
#include <chrono>
#include <iomanip>

template<typename Realtype = double>
constexpr Realtype Epsilon(const unsigned char z)
{
	return (z ? 0.1*Epsilon<Realtype>(z-1) : 1);
}

template<typename fun, typename Realtype = double>
Realtype SecantMethod(Realtype x1, Realtype x2, fun& f, unsigned int limit)
{
	Realtype f1=f(x1);
	Realtype f2=f(x2);
	Realtype x3=(f1*x2-f2*x1)/(f1-f2);
	while(std::abs(f(x3))>Epsilon<Realtype>(36) && limit--)
	{
		x1=x2;
		x2=x3;
		f1=f(x1);
		f2=f(x2);
		x3=(f1*x2-f2*x1)/(f1-f2);
	}
	return x3;
}

double Func(double x)
{
	return (x*x-1)*std::pow(std::sinh(x),3);
}

int main()
{
	static_assert(Epsilon(10)<0.000000001,"constexpr not working");
	auto Solution = SecantMethod(-1.,-0.5,Func,999999);
	if(std::abs(Func(Solution))>Epsilon(36)) std::cout << "Not OK";
	std::cout << std::setprecision(16) << Solution << std::endl;
}