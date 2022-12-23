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

        void setRe(double _a);

        void setIm(double _b);

        double getRe() const;

        double getIm() const;

        Complexe& operator=(const Complexe& c);

        Complexe& operator+=(const Complexe& c);

        Complexe& operator-=(const Complexe& c);

        Complexe& operator+(const Complexe& c);

        Complexe& operator-(const Complexe& c);

        bool operator==(const Complexe& c) const;

        bool operator!=(const Complexe& c) const;

        bool operator<(const Complexe& c) const;

        bool operator>(const Complexe& c) const;

        bool operator<=(const Complexe& c) const;

        bool operator>=(const Complexe& c) const;

        Complexe &operator+=(double d_a);

        Complexe &operator+(double d_a);

        Complexe &operator-=(double d_b);

        Complexe &operator-(double d_b);

        Complexe &operator*=(double d_c);

        Complexe &operator*(double d_c);

        Complexe &operator/=(double d_c);

        Complexe &operator/(double d_c);

        Complexe &operator*=(const Complexe& c);

        Complexe &operator*(const Complexe& c);

        Complexe &operator/=(const Complexe& c);

        Complexe &operator/(const Complexe& c);

};

#endif