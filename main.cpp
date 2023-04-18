#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "Pfloat.hpp"

int main(){

    Pfloat a(1.4);


    // std::cout << "a = " << a.toString() << "\n";
    std::cout << "a = " << a.toeString() << "\n";
    // std::cout << "a = " << a.debugToString() << "\n";

    Pfloat b(8.7);


    // std::cout << "b = " << b.toString() << "\n";
    std::cout << "b = " << b.toeString() << "\n";
    // std::cout << "b = " << b.debugToString() << "\n";

    Pfloat c(0);

    return 0;
}