#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "Pfloat.hpp"

int main(){
    // === == tests
    assert(Pfloat(2) == Pfloat(2.000000000));
    assert(Pfloat(0) == Pfloat());
    assert(Pfloat() == Pfloat());
    assert(Pfloat() == Pfloat(0));
    // === != tests
    assert(Pfloat() != Pfloat(1));
    assert(Pfloat(11) != Pfloat(1.1));
    assert(Pfloat(2) + Pfloat(22) != Pfloat());
    // === + tests
    assert(Pfloat(2) + Pfloat(2) == Pfloat(4));
    assert(Pfloat(0) + Pfloat(2) == Pfloat(2));
    assert(Pfloat(1.999998) + Pfloat(.000002) == Pfloat(2));



    Pfloat a(0.2);
    std::cout << "a = " << a.toeString() << "\n";

    Pfloat b(0.0);
    std::cout << "b = " << b.toeString() << "\n";

    std::cout << "a != b : " << (a != b) << "\n";


    return 0;
}