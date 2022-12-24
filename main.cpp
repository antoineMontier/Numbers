#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "BigInt.hpp"

int main(){

    BigInt a;

    BigInt c(5);

    BigInt k(112233445566778899);

    
    BigInt x(a), y(c), z(k);

    std::cout << a.debugToString() << std::endl;
    std::cout << c.debugToString() << std::endl;
    std::cout << k.debugToString() << std::endl;

    std::cout << x.debugToString() << std::endl;
    std::cout << y.debugToString() << std::endl;
    std::cout << z.debugToString() << std::endl;


    std::cout << "All tests passed!" << std::endl;
    return 0;
}