#ifndef PFLOAT_HPP
#define PFLOAT_HPP

#include "BigInt.hpp"

using namespace std;

class Pfloat{

    private:

        BigInt *digits;
        long exponent;

    public:

        Pfloat();

        ~Pfloat();
};



#endif