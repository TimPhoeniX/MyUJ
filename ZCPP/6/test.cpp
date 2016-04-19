#include <type_traits>
#include <iostream>
#include <typeinfo>

template<bool flag,typename T1,typename T2> struct If_then_else {
typedef T1 Result; 
};

template<typename T1,typename T2> 
struct If_then_else<false,T1,T2> {
typedef T2 Result; 
};

template<typename T> struct Is_class {
  //najpierw definiujemy dwa typy różniące sie rozmiarem
  typedef char one;
  typedef struct {char c[2];} two;
  //teraz potrzebne bedą dwa przeładowane szablony
  template<typename U> static one test(int U::*); 
  template<typename U> static two test(...);
  //to który szablon został wybrany sprawdzamy poprzez sprawdzenie rozmiaru zwracanego typu
  enum {yes = (sizeof(test<T>(0))==sizeof(one) )};
};

template<typename T,typename U> class Is_convertible {
typedef char one;
typedef struct {char c[2];} two;
static one test(U) ;
static two test(...);
static T makeT();

public: enum {yes = sizeof(test(makeT()) )==sizeof(one),
  same_type=false }; }; 

template<typename T> class Is_convertible<T,T> {
public:
  enum {yes = true,
      same_type=true }; 
};

template<typename T>
using Stripped = typename std::remove_const<typename std::remove_reference<T>::type>::type;

int main()
{
	std::cout << sizeof(If_then_else<true,bool,int>::Result) << sizeof(std::conditional<true,bool,int>::type) << std::endl;
	std::cout << sizeof(If_then_else<false,bool,int>::Result) << sizeof(std::conditional<false,bool,int>::type) << std::endl;

	std::cout << Is_class<int>::yes << std::is_class<int>::value << std::endl;
	std::cout << Is_class<std::ostream>::yes << std::is_class<std::ostream>::value << std::endl;
	
	std::cout << Is_convertible<int,double>::yes << std::is_convertible<int,double>::value << std::endl;
	
	
	
	std::cout << std::is_same<int,Stripped<const int&>>::value << std::endl;
}