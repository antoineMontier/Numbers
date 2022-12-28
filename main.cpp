#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "Pfloat.hpp"

int main(){

    Pfloat a(1234.50);
    std::cout << "\n\neee\n\n" << std::endl;
    std::cout << a.toString() << "\t" << a.debugToString()<< std::endl;

    return 0;
}