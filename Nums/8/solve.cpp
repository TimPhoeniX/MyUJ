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
Realtype SecantMethod(Realtype x1, Realtype x2, fun& f, unsigned int limit = 1000000)
{
	Realtype f1=f(x1);
	Realtype f2=f(x2);
	Realtype x3=(f1*x2-f2*x1)/(f1-f2);
	while(std::abs(f(x3))>Epsilon<Realtype>(46) && limit--)
	{
		x1=x2;
		x2=x3;
		f1=f(x1);
		f2=f(x2);
		x3=(f1*x2-f2*x1)/(f1-f2);
	}
	return x3;
}

template<typename fun, typename Realtype = double>
Realtype RegulaFalsiMethod(Realtype x1, Realtype x2, fun& f, unsigned int limit = 1000000)
{
	Realtype f1=f(x1);
	Realtype f2=f(x2);
	if(x2 < x1 || f1*f2 > 0.) return std::numeric_limits<Realtype>::quiet_NaN();
	Realtype x3=(f1*x2-f2*x1)/(f1-f2);
	Realtype f3=0;
	while(std::abs(f3=f(x3))>Epsilon<Realtype>(36) && limit--)
	{
		x1=(f1*f3 > 0. ? x3 : x1);
		x2=(f2*f3 > 0. ? x3 : x2);;
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
	for(double a = -10.; a <= 10.; a+=0.25)
	{
		for(double b = -10.; b <= 10.; b+=0.25)
		{
			if(a==b) continue;
			std::cout << a << ' ' << b << " -> ";
			auto Solution = SecantMethod(a,b,Func);
			std::cout << std::setprecision(16) << (std::abs(Func(Solution))<Epsilon(36)?Solution:std::numeric_limits<double>::quiet_NaN());
			std::cout << ", ";
			Solution = RegulaFalsiMethod(a,b,Func);
			std::cout << std::setprecision(16) << (std::abs(Func(Solution))<Epsilon(36)?Solution:std::numeric_limits<double>::quiet_NaN()) << '\n';
		}
	}
}