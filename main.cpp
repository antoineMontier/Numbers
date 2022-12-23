#include <iostream>
#include "Complexe.hpp"

int main(){
    Complexe z;
    Complexe z2(2, 9);
    Complexe z3(z2);
    std::cout << "z = " << z.toString() << std::endl;
    std::cout << "z2 = " << z2.toString() << std::endl;
    std::cout << "z3 = " << z3.toString() << std::endl;

    return 0;
}