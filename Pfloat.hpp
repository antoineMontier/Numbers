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

#define STANDARD_PRECISION 24

using namespace std;

class Pfloat{

    private:

        LinkedList<int>* digits;
        /// @brief digits*10^exponent
        long exponent;

        /// @brief we assume the exponents of the two Pfloats are the same and they are both tydied
        /// @return true if b is greater than this
        bool rec_inf(const Pfloat b, int index_cmp) const;

        bool check_string(std::string const str) const; // TODO: make this static

        bool check_exp_string(std::string const str) const; // TODO: make this static

        bool neg;

        int precision;

    public:

        Pfloat abs() const;

        Pfloat();

        ~Pfloat();

        /// @brief creates a new Pfloat from a long
        /// @param n warning, n must have less than 8 digits
        Pfloat(long double n);

        Pfloat(const Pfloat& n);

        /// @brief creates a new Pfloat from a string
        /// @param str format XXX.xxx or XXX.XXXeXXX
        Pfloat(const std::string str);

        int getExponent() const;

        const string toString() const;

        const string toeString() const;

        const string debugToString() const;

        Pfloat pow(const int& x) const;

        bool tidy();

        Pfloat operator - (const Pfloat& x) const;
        Pfloat operator - (const long double& x) const;
        Pfloat operator - (const std::string& str) const;

        Pfloat operator + (const Pfloat& x) const;
        Pfloat operator + (const long double& x) const;
        Pfloat operator + (const std::string& str) const;

        Pfloat operator * (const Pfloat& x) const;
        Pfloat operator * (const long double& x) const;
        Pfloat operator * (const std::string& str) const;

        Pfloat operator / (const Pfloat& x) const;

        Pfloat operator % (const Pfloat& p) const;

        Pfloat& operator = (const Pfloat& n);
        Pfloat& operator = (const long double& n);
        Pfloat& operator = (const std::string& str);

        bool operator == (const Pfloat& x) const;
        bool operator == (const long double& x) const;
        bool operator == (const std::string& str) const;

        bool operator != (const Pfloat& x) const;
        bool operator != (const long double& x) const;
        bool operator != (const std::string& str) const;

        bool operator < (const Pfloat& x) const;
        bool operator < (const long double& x) const;
        bool operator < (const std::string& str) const;

        bool operator <= (const Pfloat& x) const;
        bool operator <= (const long double& x) const;
        bool operator <= (const std::string& str) const;

        bool operator > (const Pfloat& x) const;
        bool operator > (const long double& x) const;
        bool operator > (const std::string& str) const;

        bool operator >= (const Pfloat& x) const;
        bool operator >= (const long double& x) const;
        bool operator >= (const std::string& str) const;
};



#endif