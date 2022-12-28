#ifndef PFLOAT_HPP
#define PFLOAT_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
#include "LinkedList.cpp"

using namespace std;

class Pfloat{

    private:

        LinkedList<int>* digits;
        /// @brief digits*10^exponent
        long exponent;

    public:

        Pfloat();

        ~Pfloat();

        Pfloat(long double n);

        Pfloat(const std::string& str);

        const string toString() const;

        const string debugToString() const;

        bool tidy();

};



#endif