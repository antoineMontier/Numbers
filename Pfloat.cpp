#include "Pfloat.hpp"

using namespace std;

Pfloat::Pfloat(){
    precision = STANDARD_PRECISION;
    exponent = 0;
    digits = new LinkedList<int>();
    neg = false;
}

Pfloat::~Pfloat(){
    delete digits;
}

const string Pfloat::toString() const{
    if(digits->size() == 0) return "0.0";
    ostringstream res("");
    if(neg) res << "-";
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
    if(neg) res << "-";
    res << digits->get(0) << ".";
    for(int i = 1; i < digits->size(); ++i) res << digits->get(i);
    if(exponent != 0) res << "e" << exponent;
    return res.str();
}

const string Pfloat::debugToString() const{
    ostringstream res("");
    if(neg) res << "-"; else res << "+";
    res << digits->toString();
    res << "\te = " << exponent;
    return res.str();
}

int Pfloat::getExponent() const{
    return exponent;
}

Pfloat::Pfloat(long double n) {
    precision = STANDARD_PRECISION;
    if(n < 0) neg = true;
    else neg = false;
    n = neg ? -n : n;
    digits = new LinkedList<int>();
    exponent = 0;
    if(n == 0.0 || n == -0.0) n = 0;
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

bool Pfloat::string_matched(std::string const str){
    std::regex pattern("^-?[0-9\\.]+$");
    if(!std::regex_match(str, pattern))
        return false;
    char*cs = (char*)malloc(str.size() + 1);
    // assert max one point
    int point_count = 0;
    for(int i = 0 ; i < (int)str.size() && point_count < 2 ; ++i)
        point_count += cs[i] == '.';
    if(point_count > 1){
        free(cs);
        return false;
    }

}   


Pfloat::Pfloat(const std::string str){
    std::cout << str << std::endl;
     // pattern to match
    if(!string_matched(str))
        throw std::runtime_error("provide a string containing only digits, optionnally one '.' and a '-' in first position");
    precision = STANDARD_PRECISION;
    if(str[0] == '-') neg = true; else neg = false;
    digits = new LinkedList<int>();

    char* arg_char = (char*)malloc(str.size()*sizeof(char) + 1);
    strcpy(arg_char, str.c_str());
    for(int i = 0; i < (int)str.size(); i++){
        // std::cout << "i = " << i << " char = " << arg_char[i] << std::endl;
        if(arg_char[i] == '.')  exponent = i-1;
        else                    digits->pushTail(arg_char[i] - '0');
    }
    free(arg_char);
    tidy();
}


bool Pfloat::tidy(){
    if(precision < 1){
        throw std::runtime_error("precision must be at least 1");
        exit(1);
    }
    // std::cout << "before" << debugToString() << "\n";
    if(digits->size() == 0) return false;
    
    // check if each slot has a value below 9 : 
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

    
    // check if each slot has a value greater than 0 : 
    for(int i = 1 ; i < digits->size() ; ++i){
        while(digits->get(i) < 0){
            digits->set(i, digits->get(i) + 10); // keep the last digit
            digits->set(i - 1, digits->get(i -1) - 1); // add
        }
    }
    // first slot case : 
    if(digits->get(0) < 0){
        neg = !neg;
        for(int i = 0; i < digits->size() ; ++i)
            digits->set(i, -digits->get(i));
        tidy();
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
    // assert precision is respected (number of digits is not too large)
    if(digits->size() > precision){
        std::cout << "need to round up " << toString() << " digits->size() = " << digits->size() << " precision = " << precision << "\n";
        if(digits->get(precision) >= 5)
            digits->set(precision - 1, digits->get(precision - 1) + 1);
        for(int i = digits->size() - 1; i >= precision  ; --i) digits->popTail();
        tidy();
    }
    return true; 
}

Pfloat::Pfloat(Pfloat const &other){
    precision = other.precision;
    digits = new LinkedList<int>();
    for(int i = 0; i < other.digits->size(); i++)
        digits->pushTail(other.digits->get(i));
    exponent = other.getExponent();
    neg = other.neg;
    tidy();
}

Pfloat Pfloat::operator + (const Pfloat& x) const{
    if(x.neg && !neg){ /*std::cout << "1e case\n";*/return *this - x.abs();}
    if(x.neg && neg){ /*std::cout << "2e case\n";*/ return Pfloat(0) - (this->abs() + x.abs());}
    if(!x.neg && neg){ /*std::cout << "3e case\n";*/ return x - this->abs();}
    // here, both this and x are positive
    // considering 'this' has an exp = e1 and 'x' has an exp = e2. the slots will correspond themselves by an offset of moving left the 'x' tab by e2 - e1
    Pfloat res(x); // copy argument
    int max_t = exponent + 1, max_x = res.getExponent() + 1, min_t = max_t - digits->size(), min_x = max_x - res.digits->size();

    // add enough slots at the beginning of the array : 
    for(int i = max_x ; i < max_t ; ++i){
        res.digits->push(0);
        res.exponent++;
    }

    // add enough slots at the end of the array
    for(int i = min_x ; i > min_t ; --i) res.digits->pushTail(0);

    // add digits from 'this' to res : 
    for(int i = 0 ; i < digits->size(); ++i)
        res.digits->set(i + res.exponent - exponent, digits->get(i) + res.digits->get(i + res.exponent - exponent));
    res.tidy();
    return res;
}

Pfloat Pfloat::operator + (const long double& x) const{return (*this) + Pfloat(x);}


Pfloat Pfloat::operator - (const Pfloat& x) const{
    if(!neg && x.neg) return *this + x.abs();
    if(neg && x.neg) return x.abs() - this->abs();
    if(neg && !x.neg) return Pfloat(0) - (this->abs() + x);
    // here, both this and x are positive
    //std::cout << "\n@@@@@\n" << debugToString() << "\n" << x.debugToString() << "\n";
    Pfloat res(x);
    int max_t = exponent + 1, max_x = res.getExponent() + 1, min_t = max_t - digits->size(), min_x = max_x - res.digits->size();
    
    for(int i = max_x ; i < max_t ; ++i){
        res.digits->push(0);
        res.exponent++;
    }
    // std::cout <<"after adding 0 " << res.debugToString() << std::endl;

    for(int i = min_x ; i > min_t ; --i) res.digits->pushTail(0);

    for(int i = 0 ; i < 0 + res.exponent - exponent ; ++i) res.digits->set(i, -res.digits->get(i)); // make negative the first numbers because they won't be handled by the loops

    for(int i = 0 ; i < digits->size(); ++i){
        //std::cout << "1st loop accessing i = " << i << " res size = " << res.digits->size() << " this size = " << digits->size() << " setting at i = " << i + res.exponent - exponent <<std::endl;
        res.digits->set(i + res.exponent - exponent, digits->get(i) - res.digits->get(i + res.exponent - exponent));
    }
    for(int i = digits->size(); i < res.digits->size(); ++i){
        //std::cout << "2nd loop accessing i = " << i << " res size = " << res.digits->size() << " this size = " << digits->size() << " setting at i = " << i + res.exponent - exponent <<std::endl;
        if(i + res.exponent - exponent < res.digits->size())
            res.digits->set(i + res.exponent - exponent, 0 - res.digits->get(i + res.exponent - exponent));
    }

    // std::cout <<"after - " << res.debugToString() << std::endl;
    res.tidy();
    return res;
}

Pfloat Pfloat::operator - (const long double& x) const{return (*this) - Pfloat(x);}


Pfloat& Pfloat::operator = (const Pfloat& n) {
    // Clear the current digits of this Pfloat
    digits->clear();

    // Copy the digits of the other Pfloat to this Pfloat
    for (int i = 0; i < n.digits->size(); i++)  digits->pushTail(n.digits->get(i));
    exponent = n.exponent;

    return *this;
}

Pfloat& Pfloat::operator = (const long double& x) {return (*this) = Pfloat(x);}


bool Pfloat::operator == (const Pfloat& x) const{
    if((digits->size() == 0 && x.digits->size() == 0) 
    || (digits->size() == 0 && x.digits->size() == 1 && x.digits->get(0) == 0)
    || (x.digits->size() == 0 && digits->size() == 1 && digits->get(0) == 0)) return true;
    // copy this and x : 
    Pfloat t = *this;
    Pfloat xx = x;
    // tidy
    t.tidy(); xx.tidy();
    if(t.neg != xx.neg) return false;
    // compare exponents and digits : 
    if(t.digits->size() != x.digits->size()) return false;
    for(int i = 0; i < t.digits->size(); ++i) if(t.digits->get(i) != x.digits->get(i)) return false;
    if(t.exponent != x.exponent) return false;
    return true; // all tests passed
}

bool Pfloat::operator == (const long double& x) const{return (*this) == Pfloat(x);}
bool Pfloat::operator != (const long double& x) const{return (*this) != Pfloat(x);}
bool Pfloat::operator > (const long double& x) const{return (*this) > Pfloat(x);}
bool Pfloat::operator < (const long double& x) const{return (*this) < Pfloat(x);}
bool Pfloat::operator >= (const long double& x) const{return (*this) >= Pfloat(x);}
bool Pfloat::operator <= (const long double& x) const{return (*this) <= Pfloat(x);}


bool Pfloat::operator != (const Pfloat& x) const {
    return !(*this == x);
}

Pfloat Pfloat::abs() const{
    Pfloat res(*this);
    res.neg = false;
    return res;
}

bool Pfloat::operator < (const Pfloat& x) const {
    if(neg == true && x.neg == false) return true;
    if(neg == false && x.neg == true) return false;
    if(neg == true && x.neg == true) return this->abs() > x.abs();
    if(*this == x) return false;
    if(exponent < x.exponent) return true;
    if(exponent > x.exponent) return false;
    // same exponents
    // copy this and x : 
    Pfloat t = *this, xx = x;
    // tidy
    t.tidy(); xx.tidy();
    return t.rec_inf(x, 0);
}

bool Pfloat::rec_inf(const Pfloat b, int index_cmp) const{
    if(digits->size() > index_cmp && b.digits->size() > index_cmp){
        if(digits->get(index_cmp) > b.digits->get(index_cmp)) return false;
        if(digits->get(index_cmp) < b.digits->get(index_cmp)) return true;
        return rec_inf(b, index_cmp + 1); // recursion
    }else if(digits->size() == index_cmp && b.digits->size() > index_cmp) return true;// b is larger
    else if(digits->size() > index_cmp && b.digits->size() == index_cmp) return false;
    else return false; // same size of digits arrays so they are equals
}

bool Pfloat::operator <= (const Pfloat& x) const {
    return (*this < x) || (*this == x);
}

bool Pfloat::operator > (const Pfloat& x) const {
    return !(*this <= x);
}

bool Pfloat::operator >= (const Pfloat& x) const {
    return !(*this < x);
}

Pfloat Pfloat::operator * (const Pfloat& x) const{
    // === quick cases ===
    if(x == Pfloat(0) || *this == Pfloat(0)) return Pfloat(0);
    if(x == Pfloat(1)) return Pfloat(*this);
    if(*this == Pfloat(1)) return Pfloat(x);
    if(x == Pfloat(-1)){
        Pfloat r(*this);
        r.neg = !r.neg;
        return r;
    }
    if(*this == Pfloat(-1)){
        Pfloat r(x);
        r.neg = !r.neg;
        return r;
    }
    Pfloat res;
    res.exponent = x.exponent;
    // =============================== add slots to res
    
    for(int i = 0 ; i < digits->size() + x.digits->size(); ++i) res.digits->push(0);

    // ===============================
    // std::cout << "about to multiply " << debugToString() << "\nand" << x.debugToString() << "\nbefore mult : " << res.debugToString() << std::endl;

    // multiply the numbers using this rule : foreach slots of number1, multiply if with the slots of number2 and store the result at slot index : e1 + e2 - slot_n1 - slot_n2
    int index;   
    for(int i = 0 ; i < digits->size(); ++i){
        for(int j = 0 ; j < x.digits->size() ; ++j){
            index = (i + j);
            // std::cout << "index = " << index << "\t" << res.debugToString() << "\n\t= " << res.digits->get(index) << " + " << digits->get(i) << " * " << x.digits->get(j) << "\n";
            res.digits->set(index, res.digits->get(index) + digits->get(i) * x.digits->get(j));
        }
    }
    res.digits->reverse();
    // std::cout << "after mult : " << res.debugToString() << std::endl;
    // set the exponent of the result
    res.exponent = exponent + x.exponent;
    res.tidy();
    // std::cout << res.toString() << std::endl;
    // manage sign : 
    if(x.neg == this->neg) res.neg = false;
    else res.neg = true;
    return res;
}

Pfloat Pfloat::operator * (const long double& x) const{return (*this) * Pfloat(x);}

Pfloat Pfloat::pow(const int& n) const{
    // quick cases
    if(n < 0) {
        std::cout << "pow method not implemented for negative power yet!" << std::endl;
        return Pfloat(1);
    } 
    if(n == 0) return Pfloat(1);
    if(*this == 1) return Pfloat(1);
    if(*this == 0) return Pfloat(0);
    if(n == 1) return Pfloat(*this);
    if(n == 2) return Pfloat(*this)*Pfloat(*this);
    if(n == 3) return Pfloat(*this)*Pfloat(*this)*Pfloat(*this);
    if(n % 2 == 0) return Pfloat(*this).pow(n/2).pow(2); // even
    else return Pfloat(*this).pow(n/2).pow(2)*Pfloat(*this); // odd
}
