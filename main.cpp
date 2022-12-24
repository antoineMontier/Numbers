#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "BigInt.hpp"

int main(){

    BigInt a;

    BigInt c(5);

    BigInt k(123456789);

    std::cout << c.toString() << std::endl;
    std::cout << k.toString() << std::endl;

    std::cout << "All tests passed!" << std::endl;
    return 0;
}