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
    // display first zeros : 
    
    if(exponent < -1){
        int z = exponent;
        res << "0.";
        while(z++ + 1 < 0)
            res << "0";
    }else if(exponent == -1) res << "0";
    for(int i = 0 ; i < digits->size() ; i++ ){
        if(exponent == i-1) res << ".";
        res << digits->get(i);
    }
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
    // remove leading zeros
    int i = 0;
    while(digits->get(i) == 0){
        i++;    
        exponent--;
        // std::cout << "1 zero at beginning of list" << std::endl;
    } 
    if(i != 0) for(int j = 0 ; j < i ; j++) digits->pop();

    // remove trailing zeros
    int static_size = digits->size();
    i = static_size - 1;
    while(digits->get(i) == 0){
        i--;
        //std::cout << "1 zero at end of list" << std::endl;
    }
    if(i != static_size - 1)
        for(int j = i ; j < static_size - 1 ; j++){
            //std::cout << "1 for it" << std::endl;
            digits->popTail();
        }
    
    return true;
}
