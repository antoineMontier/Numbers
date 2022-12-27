#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "Pfloat.hpp"

int main(){

    Pfloat a(1.23456789);
    std::cout << "\n\neee\n\n" << std::endl;
    std::cout << a.toString() << std::endl;

    return 0;
}