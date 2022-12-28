#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "Pfloat.hpp"

int main(){

    Pfloat a("12.50");
    Pfloat b("1900.0");
    std::cout << "a = " << a.toString() << "\nb = " << b.toString() << "\na + b = " << (a+b).toString()<< std::endl;

    return 0;
}