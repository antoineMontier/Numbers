#ifndef COMPLEXE_HPP
#define COMPLEXE_HPP

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class Complexe{
    private :
        double a, b;

    public:
    
        Complexe();

        Complexe(double _a, double _b);

        Complexe(const Complexe& c);

        const string toString() const;
};

#endif