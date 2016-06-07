#include <algorithm>
#include <complex>
#include <iostream>

template <typename Iter>
void print_on_cout(Iter b, Iter e)
{
    if (b == e) {
        return;
    }
    while (true) {
        std::cout << *b;
        ++b;
        if (b == e) {
            break;
        }
        std::cout << ' ';
    }
    std::cout << '\n';
}

struct plus_dwa {
    typedef int argument_type;
    typedef int result_type;

    int operator()(int x) const {
        return x + 2;
    }
};

struct do_kwadratu {
    typedef int argument_type;
    typedef int result_type;

    int operator()(int x) const {
        return x * x;
    }
};

// *** tu możesz wpisać swój kod, jeśli chcesz ***

int main()
{
    int dane[5] = { 7, 2, 6, 4, 5 };
    int wyniki[5];

    print_on_cout(dane, dane+5);        // powinno wypisać 7 2 6 4 5

    plus_dwa f;
    std::transform(dane, dane+5, wyniki, f);
    print_on_cout(wyniki, wyniki+5);    // powinno wypisać 9 4 8 6 7

    do_kwadratu g;
    std::transform(dane, dane+5, wyniki, g);
    print_on_cout(wyniki, wyniki+5);    // powinno wypisać 49 4 36 16 25

    auto h = [f,g](int x)->int {return f(g(x));};
    std::transform(dane, dane+5, wyniki, h);
    print_on_cout(wyniki, wyniki+5);    // powinno wypisać 51 6 38 18 27

    return 0;
}