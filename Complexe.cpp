#include "Complexe.hpp"

using namespace std;

Complexe::Complexe(){
    a = 0;
    b = 0;
}

Complexe::Complexe(double _a, double _b){
    a = _a;
    b = _b;
}

Complexe::Complexe(const Complexe& c){
    a = c.a;
    b = c.b;
}

const string Complexe::toString() const
{
    ostringstream res;
    res << a << " + i" << b;
    return res.str();
}

void Complexe::setRe(double _a){a = _a;}

void Complexe::setIm(double _b){b = _b;}

double Complexe::getRe() const{return a;}

double Complexe::getIm() const{return b;}

Complexe& Complexe::operator=(const Complexe& c){
    a = c.a;
    b = c.b;
    return *this;
}

Complexe& Complexe::operator+=(const Complexe& c){
    a += c.a;
    b += c.b;
    return *this;
}


Complexe& Complexe::operator-=(const Complexe& c){
    a -= c.a;
    b -= c.b;
    return *this;
}

Complexe& Complexe::operator+(const Complexe& c){
    Complexe *res = new Complexe(*this);
    res->a += c.a;
    res->b += c.b;
    return *res;
}

Complexe& Complexe::operator-(const Complexe& c){
    Complexe *res = new Complexe(*this);
    res->a -= c.a;
    res->b -= c.b;
    return *res;
}