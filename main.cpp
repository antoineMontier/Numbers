#include <iostream>
#include <assert.h>
#include "Complexe.hpp"

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


    std::cout << "All tests passed!" << std::endl;
    return 0;
}