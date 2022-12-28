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
    digits = new LinkedList<int>();
    exponent = 0;
    std::string s = std::to_string(n);
    int nbdigts = s.size();
    for(long unsigned int i = 0; i < s.size(); i++)
        std::cout << " i =  " << i << " c = " << s.at(i) << std::endl;
    
    if(s.find(".") != std::string::npos){//if there is a dot in the string
        nbdigts--;
        exponent = s.find(".");
        std::cout << exponent << "   " << s.at(exponent) << std::endl;

        s.erase(exponent, 1);
    }else
        exponent = 0; //int number
    // add each number in the linked list
    std::cout << "--------------------" << std::endl;
    long int number_no_dot = atoi(&(s.at(0)));
    while(number_no_dot > 0){
        digits->push(number_no_dot %10);
        number_no_dot /= 10;
    }



    /*std::cout << n << std::endl;
    long double decimalp = n;
    long double intp;

    do {
        decimalp = std::modf(n, &intp);
        std::cout << "d  = " << decimalp << "  \tint = " << intp << std::endl;
        n *= 10;
        exponent--;
    } while (decimalp > 0);
    int nn = std::nearbyint(intp);
    std::cout << "\n\n" << nn << "\t" << intp << std::endl;
    int num_digits = std::floor(std::log10(n)) + 1;
    while(num_digits > 0){
        digits->push(nn %10);
        nn /= 10;
        num_digits--;
    }*/
}


const string Pfloat::toString() const{
    ostringstream res("");
    for(int i = 0 ; i < digits->size() ; i++ ){
        if(exponent == i) res << ".";
        res << digits->get(i);
    }
    std::cout << res.str() << std::endl;
    return res.str();
}

const string Pfloat::debugToString() const{
    return digits->toString();
}
