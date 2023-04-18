#include "Pfloat.hpp"

using namespace std;

Pfloat::Pfloat(){
    exponent = 0;
    digits = new LinkedList<int>();
}

Pfloat::~Pfloat(){
    delete digits;
}

const string Pfloat::toString() const{
    if(digits->size() == 0) return "0.0";
    ostringstream res("");
    // display first zeros if exponent is negative : 
    if(exponent < -1){
        int z = exponent;
        res << "0.";
        while(z++ + 1 < 0) res << "0";
    }else if(exponent == -1) res << "0";

    for(int i = 0 ; i < digits->size() ; i++ ){
        if(exponent == i-1) res << ".";
        res << digits->get(i);
    }
    // add zeros at the end if needed
    for(int i = digits->size() ; i <= exponent ; ++i) res << "0";
    return res.str();
}

const string Pfloat::toeString() const{
    if(digits->size() == 0) return "0.0";
    ostringstream res("");
    res << digits->get(0) << ".";
    for(int i = 1; i < digits->size(); ++i) res << digits->get(i);
    if(exponent != 0) res << "e" << exponent;
    return res.str();
}


const string Pfloat::debugToString() const{
    return digits->toString();
}

int Pfloat::getExponent() const{
    return exponent;
}

Pfloat::Pfloat(long double n) {
    digits = new LinkedList<int>();
    exponent = 0;
    std::string s = std::to_string(n);
    char* arg_char = (char*)malloc(s.size()*sizeof(char) + 1);
    strcpy(arg_char, s.c_str());

    for(int i = 0; i < (int)s.size(); i++){
        if(arg_char[i] == '.')  exponent = i-1;
        else                    digits->pushTail(arg_char[i] - '0');
    }
    free(arg_char);
    tidy();
}

bool Pfloat::tidy(){
    if(digits->size() == 0) return false;
    
    // check if each slot has a value between 0 and 9 : 
    for(int i = digits->size() - 1 ; i > 0 ; --i){
        if(digits->get(i) > 9){
            int tmp = digits->get(i) / 10; // get the overflow value
            digits->set(i, digits->get(i) % 10); // keep the last digit
            digits->set(i - 1, tmp + digits->get(i -1)); // add
        }
    }
    // first slot case : 
    if(digits->get(0) > 9){
        digits->push(digits->get(0) / 10);
        digits->set(1, digits->get(1) % 10); // first slot is now slot n°1
        exponent++;
    }

        // remove leading zeros
    int i = 0;
    while(i < digits->size() && digits->get(i) == 0){
        i++;    
        exponent--;
    } 
    if(i != 0) for(int j = 0 ; j < i ; j++) digits->pop();

    // remove trailing zeros
    int static_size = digits->size();
    i = static_size - 1;
    while(i >= 0 && digits->get(i) == 0)--i;
    if(i != static_size - 1) for(int j = i ; j < static_size - 1 ; j++) digits->popTail();



    return true;
}

Pfloat::Pfloat(Pfloat const &other){
    digits = new LinkedList<int>();
    for(int i = 0; i < other.digits->size(); i++)
        digits->pushTail(other.digits->get(i));
    exponent = other.getExponent();
    tidy();
}

Pfloat Pfloat::operator + (const Pfloat& x) const{
    // considering 'this' has an exp = e1 and 'x' has an exp = e2. the slots will correspond themselves by an offset of moving left the 'x' tab by e2 - e1
    Pfloat res(x); // copy argument
    int max_t = exponent + 1, max_x = res.getExponent() + 1, min_t = max_t - digits->size(), min_x = max_x - res.digits->size();
    // std::cout << "t = " << toeString() << "\nx = " << res.toeString() << "\n";
    // std::cout << "min_t = " << min_t << "\nmax_t = " << max_t << "\nmin_x = " << min_x << "\nmax_x = " << max_x << "\n";
    
    // add enough slots at the beginning of the array : 
    for(int i = max_x ; i < max_t ; ++i){
        res.digits->push(0);
        res.exponent++;
    }

    // add enough slots at the end of the array
    for(int i = min_x ; i > min_t ; --i) res.digits->pushTail(0);

    // std::cout << res.debugToString() << std::endl;

    // add digits from 'this' to res : 
    int tt, xx;   
    for(int i = 0 ; i < digits->size(); ++i){
        // std::cout <<"i = "<< i << std::endl;
        tt = digits->get(i);
        // std::cout <<"tt = " <<tt << std::endl;
        xx = res.digits->get(i + res.exponent - exponent);
        // std::cout <<"xx = "<<xx << std::endl;
        res.digits->set(i + res.exponent - exponent, tt + xx);
    }
    
    res.tidy();
    // std::cout << res.toString() << std::endl;
    // std::cout << res.debugToString() << std::endl;

    return res;

}

Pfloat& Pfloat::operator=(const Pfloat& n) {
    // Clear the current digits of this Pfloat
    digits->clear();

    // Copy the digits of the other Pfloat to this Pfloat
    for (int i = 0; i < n.digits->size(); i++)  digits->pushTail(n.digits->get(i));
    exponent = n.exponent;

    return *this;
}

bool Pfloat::operator == (const Pfloat& x) const{
    if(digits->size() == 0 && x.digits->size() == 0) return true;
    // copy this and x : 
    Pfloat t = *this;
    Pfloat xx = x;
    // tidy
    t.tidy(); xx.tidy();
    // compare exponents and digits : 
    if(t.digits->size() != x.digits->size()) return false;
    for(int i = 0; i < t.digits->size(); ++i) if(t.digits->get(i) != x.digits->get(i)) return false;
    if(t.exponent != x.exponent) return false;
    return true; // all tests passed
}
