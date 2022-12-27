#include "Pfloat.hpp"

using namespace std;

Pfloat::Pfloat(){
    exponent = 1;
    digits = new BigInt();
}


Pfloat::~Pfloat(){
    delete digits;
}