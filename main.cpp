#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "BigInt.hpp"

int main(){

    // Test the addition operator
    Complexe a(2, 3);
    Complexe b(4, 5);
    Complexe c = a + b;
    assert(c.getRe() == 6 && c.getIm() == 8);

    // Test the subtraction operator
    c = a - b;
    assert(c.getRe() == -2 && c.getIm() == -2);

    // Test the multiplication operator
    c = a * b;
    assert(c.getRe() == -7 && c.getIm() == 22);

    // Test the division operator
    c = a / b;
    assert(c.getRe() == (23.0 / 41.0) && c.getIm() == (2.0/ 41.0));

    // Test the equality operator
    assert(a == a);
    assert(!(a == b));

    // Test the inequality operator
    assert(a != b);
    assert(!(a != a));

    // Test the greater than operator
    assert(b > a);
    assert(!(a > b));


    // Test the less than operator
    assert(a < b);
    assert(!(b < a));

    // Test the setRe and getRe methods
    a.setRe(10);
    assert(a.getRe() == 10);

    // Test the setIm and getIm methods
    a.setIm(15);
    assert(a.getIm() == 15);

    //test the conjugate
    c = a.conjugate();
    assert(c.getRe() == a.getRe() && c.getIm() == -a.getIm());

    //test module and conjugate
    c = a.conjugate()*a;
    assert(c.getRe() == a.abs()*a.abs());

    //test rotation
    c = a;
    c.rotate(PI);
    assert((c  + a).abs() < 0.001);

    //test the exponent
    assert((a^1) == a);
    assert((a^0) == Complexe(1, 0));

    assert(Complexe::distance(Complexe(0, 0), Complexe(3, 4)) == 5.0);

/*
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
    assert(BigInt(9) % BigInt(1) == BigInt(0));
    assert(a % BigInt(100000) == BigInt(11111));
    assert(a % a == BigInt(0));
    assert(a % BigInt(0) == BigInt(0));
    assert(c == c / b + c % b);
    a *= BigInt(0);
    assert(a == 0);
    a += BigInt(15);
    assert(a == 15);
    a -= BigInt(20);
    assert(a == 0);
    a += BigInt(180);
    a *= BigInt(2);
    a /= BigInt(10);
    assert(a == 36);
    a *= 0;
    assert(a == 0);
    a += 15;
    assert(a == 15);
    a -= 20;
    assert(a == 0);
    a += 180;
    a *= 2;
    a /= 10;
    assert(a == 36);
    assert(a - 0 == a);
    assert(a*b - a*1 == a * (b - 1));
    assert( a * 0 == 0);
    assert( a * 1 == a);

    assert(BigInt::factorial(5) == 120);
    assert(BigInt::factorial(0) == 1 && BigInt::factorial(1) == 1);
    assert(BigInt::factorial(80) == BigInt::factorial(79)*80);
    assert(BigInt::fibonnacci(10) == 55);
*/

    std::cout << "All tests passed!" << std::endl;
    return 0;
}