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
    assert(!(a!= a));
    assert(!(a < a));
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
    assert(k + k + k + k + f == c);
    assert(k - k + k == k);
    assert(a - b < k);
    assert(c - (k*k) == BigInt(16));
    assert(a*a - a - b*a == BigInt(0));
    assert(a*b -  BigInt(0) == a*b);
    assert(a / a == BigInt(1));
    assert(BigInt(9) + BigInt(1) == BigInt(10));
    assert((a * c) / a == c );



    std::cout << "All tests passed!" << std::endl;
    return 0;
}