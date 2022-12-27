#include "Pfloat.hpp"

using namespace std;

Pfloat::Pfloat(){
    exponent = 0;
    digits = new BigInt();
}


Pfloat::~Pfloat(){
    delete digits;
}

Pfloat::Pfloat(long double n) {
    BigInt r;
    long double decimalp = n;
    long double intp;
    exponent = 0;
    do {
        decimalp = std::modf(n, &intp);
        std::cout << " d  = " << decimalp << "   int = " << intp << std::endl;
        n *= 10;

        if (decimalp > 0) exponent--;
    } while (decimalp > 0);
    digits = new BigInt(static_cast<long int>(n));
}


const string Pfloat::toString() const{
    ostringstream res("");
    for(int i = 0 ; i < digits->getDigits()->size() ; i++ ){
        if(exponent == digits->getDigits()->size() -1 - i) res << ".";
        res << digits->getDigits()->get(i);
    }
    std::cout << res.str() << std::endl;
    //return res.str();
    return digits->debugToString();
}