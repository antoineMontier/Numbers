#include "Pfloat.hpp"

using namespace std;

Pfloat::Pfloat(){
    exponent = 0;
    digits = new BigInt();
}


Pfloat::~Pfloat(){
    delete digits;
}

Pfloat::Pfloat(long double n){
    digits = new BigInt();
    long double intp, decimalp = n;
    exponent = 0;
    do{
        decimalp = std::modf(decimalp, &intp);
        std::cout << " d  = " << decimalp << "   int = " << intp << std::endl;
        (*digits) *= 10;
        (*digits) += intp;
        decimalp *= 10;
        if(decimalp > 0)
            exponent++;
    }while(decimalp > 0);
}

const string Pfloat::toString() const{
    ostringstream res;
    for( int i = 0 ; i < digits->getDigits()->size() ; i++ ){
        if( exponent  == digits->getDigits()->size() -1 - i)
            res << ".";
        res << digits->getDigits()->get(i);
    }
    return res.str();
}