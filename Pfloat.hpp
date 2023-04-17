#ifndef PFLOAT_HPP
#define PFLOAT_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
#include <string.h>
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

        /// @brief creates a new Pfloat from a long
        /// @param n warning, n must have less than 8 digits
        Pfloat(long double n);

        // Pfloat(const std::string& str);

        Pfloat(const Pfloat& n);

        int getExponent() const;

        const string toString() const;

        const string toeString() const;

        const string debugToString() const;

        bool tidy(); // todo : fix slots with numbers < 0 || > 9 

        Pfloat operator + (const Pfloat& x) const;


};



#endif