#ifndef PFLOAT_HPP
#define PFLOAT_HPP

#include "LinkedList.hpp"

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

        const string toString() const;
};



#endif