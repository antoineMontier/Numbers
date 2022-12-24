#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "BigInt.hpp"

int main(){

    BigInt a;

    BigInt c(5);

    BigInt k(3);

    std::cout << " a = " << a.debugToString() << std::endl;
    std::cout << " c = " << c.debugToString() << std::endl;
    std::cout << " k = " << k.debugToString() << std::endl;

    std::cout << " k + a = " << (k + a).debugToString() << std::endl;
    std::cout << " k + c = " << (k + c).debugToString() << std::endl;
    std::cout << " k + c + a + k = " << (k + c + a + k).debugToString() << std::endl;


    std::cout << "All tests passed!" << std::endl;
    return 0;
}