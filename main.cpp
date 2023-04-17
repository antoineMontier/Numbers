#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "Pfloat.hpp"

int main(){

    Pfloat a(.123456789);

    std::cout << "a = " << a.toString() << "\n";
    std::cout << "aa = " << a.debugToString() << "\n";
    std::cout << "exp = " << a.getExponent() << "\n";

    a.tidy();

    std::cout << "a = " << a.toString() << "\n";
    std::cout << "aa = " << a.debugToString() << "\n";
    std::cout << "exp = " << a.getExponent() << "\n";

    return 0;
}