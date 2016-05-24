#include <iostream>
#include <list>
#include <vector>

// *** tu wpisz swój kod ***
#include <type_traits>

template<typename T> struct zmiennoprzecinkowy: public std::false_type{};
template<> struct zmiennoprzecinkowy<float> : public std::true_type{};
template<> struct zmiennoprzecinkowy<double> : public std::true_type{};

int main()
{
    // drukuj wartości logiczne jako true/false, a nie 1/0
    std::cout << std::boolalpha;

    // powinno wypisać true
    std::cout << zmiennoprzecinkowy<float>::value << '\n';
    std::cout << zmiennoprzecinkowy<double>::value << '\n';

    // powinno wypisać false
    std::cout << zmiennoprzecinkowy<int>::value << '\n';
    std::cout << zmiennoprzecinkowy<char>::value << '\n';
    std::cout << zmiennoprzecinkowy< std::list<float> >::value << '\n';
    std::cout << zmiennoprzecinkowy< std::vector<long> >::value << '\n';

    return 0;
}