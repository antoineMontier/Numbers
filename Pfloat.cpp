#include "Pfloat.hpp"

using namespace std;

Pfloat::Pfloat(){
    exponent = 0;
    digits = new LinkedList<int>();
}


Pfloat::~Pfloat(){
    delete digits;
}

Pfloat::Pfloat(long double n) {
    long double decimalp = n;
    long double intp;
    digits = new LinkedList<int>();

    exponent = 0;
    do {
        decimalp = std::modf(n, &intp);
        std::cout << " d  = " << decimalp << "   int = " << intp << std::endl;
        n *= 10;

        if (decimalp > 0) exponent--;
    } while (decimalp > 0);


}


const string Pfloat::toString() const{
    ostringstream res("");
    for(int i = 0 ; i < digits->size() ; i++ ){
        if(exponent == digits->size() -1 - i) res << ".";
        res << digits->get(i);
    }
    std::cout << res.str() << std::endl;
    //return res.str();
    return digits->toString();
}