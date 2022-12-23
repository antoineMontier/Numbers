#include <iostream>
#include "Complexe.hpp"

int main(){
    Complexe z;
    Complexe z2(2, 9);
    Complexe z3(z2);
    Complexe z4;
    z2.setIm(-8);
    z.setRe(140);
    z4 = z3;
    z3.setIm(500);
    z4.setRe(340);
    z2+=z3;
    std::cout << "z = " << z.toString() << std::endl;
    std::cout << "z2 = " << z2.toString() << std::endl;
    std::cout << "z3 = " << z3.getRe() << " + i"<< z3.getIm() << std::endl;
    std::cout << "z4 = " << z4.toString() << std::endl;

    std::cout << "z - z2 = " << (z - z2).toString() << std::endl;
    std::cout << "z2 + z3 = " << (z2 + z3).toString() << std::endl;

    std::cout << "z = " << z.toString() << std::endl;
    std::cout << "z2 = " << z2.toString() << std::endl;
    std::cout << "z3 = " << z3.toString() << std::endl;
    std::cout << "z4 = " << z4.toString() << std::endl;

    return 0;
}