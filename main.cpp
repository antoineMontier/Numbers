#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "Pfloat.hpp"

int main(){

    Pfloat a(0.2);
    std::cout << "a = " << a.toeString() << "\n";

    Pfloat b(0.0);
    std::cout << "b = " << b.toeString() << "\n";

    std::cout << "a == b : " << (a == b) << "\n";


    return 0;
}