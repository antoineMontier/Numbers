#include <iostream>
#include "Complexe.hpp"

int main(){
    Complexe a(0, 0);
    Complexe b(0, -5);
    Complexe c(2, 9);
    Complexe d(5, -7);
    Complexe e(-2, -3);

    std::cout << "a = " << a.toString() << std::endl;
    std::cout << "b = " << b.toString() << std::endl;
    std::cout << "c = " << c.toString() << std::endl;
    std::cout << "d = " << d.toString() << std::endl;
    std::cout << "e = " << e.toString() << std::endl;
    
    std::cout << "a + b = " << (a + b).toString() << std::endl;
    std::cout << "b + c = " << (b + c).toString() << std::endl;
    std::cout << "a / b = " << (a / b).toString() <<std::endl;
    std::cout << "d / b = " << (d / b).toString() <<std::endl;
    std::cout << "b * c = " << (b * c).toString() << std::endl;
    std::cout << "a * e = " << (a * e).toString() << std::endl;
    std::cout << "c / c = " << (c / c).toString() << std::endl;
    std::cout << "b - b = " << (b - b).toString() << std::endl;
    std::cout << "(b + c)*8 = " << ((b + c)*8).toString() << std::endl;
    std::cout << "(b + c ) = " << ((b + c )).toString() << std::endl;
    std::cout << "(b + c - 2) = " << ((b + c - 2)).toString() << std::endl;
    std::cout << "(b + c - 2)/8 = " << ((b + c - 2)/8).toString() << std::endl;
    std::cout << "c* d = " << (c*d).toString() << std::endl;
    std::cout << "c* d / c = " << ((c*d)/c).toString() << std::endl;
    std::cout << "d / c = " << (d/c).toString() << std::endl;
    std::cout << "b > c = " << (b > c) << std::endl;
    std::cout << "d != e = " << (d != e) << std::endl;



    return 0;
}