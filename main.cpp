#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "BigInt.hpp"

int main(){

    BigInt a(12345);
    BigInt b(67890);

    BigInt c(25);
    BigInt f(13);
    BigInt k(3);

    std::cout << " a = " << a.debugToString() << std::endl;
    std::cout << " c = " << c.debugToString() << std::endl;
    std::cout << " k = " << k.debugToString() << std::endl;

    std::cout << " k + a = " << (k + a).debugToString() << std::endl;
    std::cout << " k + c = " << (k + c).debugToString() << std::endl;
    std::cout << " k + c + a + k = " << (k + c + a + k).debugToString() << std::endl;
    std::cout << " k * c = " << (k * c).debugToString() << std::endl;
    std::cout << " c * k = " << (c * k).debugToString() << std::endl;
    std::cout << " k * a = " << (k * a).debugToString() << std::endl;
    std::cout << " f * c = " << (f * c).debugToString() << std::endl;
    std::cout << " c * f = " << (c * f).debugToString() << std::endl;
    std::cout << "a * b = " << (a * b).debugToString() << std::endl;

    std::cout << "All tests passed!" << std::endl;
    return 0;
}