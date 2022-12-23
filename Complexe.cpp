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
