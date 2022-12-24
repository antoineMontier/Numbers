#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "BigInt.hpp"

int main(){

    BigInt a(1111111111);
    BigInt b(1111111110);

    BigInt c(25);
    BigInt f(13);
    BigInt k(3);


    assert( a == a);
    assert( a!= b);
    assert( a!= c);
    assert(!( a!= a));
    assert(! (a < a));
    assert(!( a < b));
    assert( ( f * k ) == f + f + f);
    assert( ( a * k ) == a + a + a);
    assert(!(a * b < a));
    assert(!(b * c < b));
    assert(!(c * f < c));
    assert( f >= f);
    assert( f <= f);
    assert(!(f > f));
    assert((f < b));
    assert((b > f));


    std::cout << "All tests passed!" << std::endl;
    return 0;
}