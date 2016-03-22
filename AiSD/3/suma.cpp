#include <iostream>

#include <iomanip>
#include <ctime>

double SumOfOnes(int n)
{
	if(n==1)
		return 1.;
	else
		return 1.+SumOfOnes(n-1);
}

double TailSum(int n, double s)
{
	if(n==1)
		return s;
	else
		return TailSum(n-1, s+1.);
}

double EliminatedTailSum(int n, double s)
{
	lab:
	if(n==1)
		return s;
	else
	{ n = n - 1; s = s + 1; goto lab; }
}

int main(void)
{
	constexpr int NumberOfExecutions = 2000000;
	constexpr int BiggerNumber = NumberOfExecutions*100;
	
	std::cout << "Testing for processor ticks\n";
	
	volatile std::clock_t t1 = std::clock();
	double ts = TailSum(NumberOfExecutions,1);
	t1 = std::clock() - t1;
	std::cout << "Suma ogonowa: " << std::setw(10) << ts << " clock ticks: " << t1 << '\n';
	
	volatile std::clock_t t2 = std::clock();
	double s = SumOfOnes(NumberOfExecutions);
	t2 = std::clock() - t2;
	std::cout << "Suma jedynek: " << std::setw(10) << s << " clock ticks: " << t2 << '\n';
	
	std::cout << "Testing for stack overflow\n";
	
	volatile std::clock_t t3 = std::clock();
	ts = TailSum(BiggerNumber,1);
	t3 = std::clock() - t3;
	std::cout << "Suma ogonowa: " << std::setiosflags(std::ios::fixed) << std::setprecision(0)<< std::setw(10) << ts << " clock ticks: " << t3 << '\n';
	
	volatile std::clock_t t4 = std::clock();
	// Komilacja przez G++ z -O2 i -O3 doprowadzi do przepełnienia stosu w tym wywolaniu
	s = SumOfOnes(BiggerNumber);
	t4 = std::clock() - t4;
	std::cout << "Suma jedynek: " << std::setiosflags(std::ios::fixed) << std::setprecision(0) << std::setw(10) << s << " clock ticks: " << t4 << '\n';
	
	volatile std::clock_t t5 = std::clock();
	// Komilacja przez G++ z -O2 i -O3 doprowadzi do przepełnienia stosu w tym wywolaniu
	s = EliminatedTailSum(BiggerNumber,1);
	t5 = std::clock() - t5;
	std::cout << "Suma GOTO   : " << std::setiosflags(std::ios::fixed) << std::setprecision(0) << std::setw(10) << s << " clock ticks: " << t5 << '\n';
	
	
	return 0;
}