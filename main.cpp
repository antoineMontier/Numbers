#include <iostream>
#include "Complexe.hpp"

int main(){
    Complexe z;
    Complexe z2(2, 9);
    Complexe z3(z2);
    z2.setIm(-8);
    z.setRe(140);
    std::cout << "z = " << z.toString() << std::endl;
    std::cout << "z2 = " << z2.toString() << std::endl;
    std::cout << "z3 = " << z3.getRe() << " + i"<< z3.getIm() << std::endl;

    return 0;
}