#include <fstream>
class NoLoggingPolicy;

template <typename T, int N = 100, typename logger = NoLoggingPolicy>
class Stack : private logger {
    T _rep[N];
    int _top;
public:
    Stack() : _top(0)
    { }
    void push(const T & val)
    {	
		logger::log_push(val);
        _rep[_top++] = val;
    }
    void pop()
    {
		logger::log_pop(_rep[_top - 1]);
        --_top;
    }
    const T & top() const
    {
        return _rep[_top - 1];
    }
    bool empty() const
    {
        return _top == 0;
    }
};

class NoLoggingPolicy
{
protected:
	template<typename T>
	void log_pop(const T& val)
	{}
	
	template<typename T>
	void log_push(const T& val)
	{}
};

class FileLoggingPolicy
{
	std::ofstream log;
protected:
	FileLoggingPolicy()
	{
		log.open("log.txt");
	}
	
	~FileLoggingPolicy()
	{
		log.close();
	}
	
	template<typename T>
	void log_pop(const T& val)
	{
		log << "popped " << val << std::endl;
	}
	
	template<typename T>
	void log_push(const T& val)
	{
		log << "pushed " << val << std::endl;
	}
};

int main()
{
	Stack<double, 100, FileLoggingPolicy> s;
	s.push(1);
	s.push(2.5);
	s.pop();
	s.push(7);
	s.pop();
	s.pop();
}
/*
to w log.txt powinny pojawić się następujące linie:
pushed 1
pushed 2.5
popped 2.5
pushed 7
popped 7
popped 1
Nie musisz dbać o wydajność. W szczególności możesz dla każdego wywołania metod push i pop otwierać plik dziennika zdarzeń w trybie dopisywania na koniec, zapisywać pojedynczy komunikat, i zamykać plik.*/