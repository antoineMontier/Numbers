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

        /// @brief we assume the exponents of the two Pfloats are the same and they are both tydied
        /// @return true if b is greater than this
        bool rec_inf(const Pfloat b, int index_cmp) const;

    public:

        Pfloat();

        ~Pfloat();

        /// @brief creates a new Pfloat from a long
        /// @param n warning, n must have less than 8 digits
        Pfloat(long double n);

        Pfloat(const Pfloat& n);

        int getExponent() const;

        const string toString() const;

        const string toeString() const;

        const string debugToString() const;

        bool tidy();

        Pfloat operator + (const Pfloat& x) const;

        Pfloat& operator = (const Pfloat& n);

        bool operator == (const Pfloat& x) const;

        bool operator != (const Pfloat& x) const;

        bool operator < (const Pfloat& x) const;

};



#endif