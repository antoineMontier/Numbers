#ifndef COMPLEXE_HPP
#define COMPLEXE_HPP

#include "Pfloat.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#define PI 3.141592653589793238462643383279502884197169

using namespace std;

class Complexe{
    private :
        Pfloat a, b;

    public:
    
        /// @brief create 0 + 0i
        Complexe();

        /// @brief create a + bi
        /// @param _a real number
        /// @param _b imaginary number
        Complexe(Pfloat _a, Pfloat _b);

        /// @brief copy a complexe number
        /// @param c the number to copy
        Complexe(const Complexe& c);

        /// @brief representation of complexe number
        /// @return a complexe number representation " a + bi"
        const string toString() const;

        /// @brief set the real number
        /// @param _a new real number
        void setRe(Pfloat _a);

        /// @brief set the imaginary number
        /// @param _b new imaginary number
        void setIm(Pfloat _b);

        /// @brief get the real number
        /// @return real number
        Pfloat getRe() const;

        /// @brief get the imaginary number
        /// @return imaginary number
        Pfloat getIm() const;

        Complexe& operator=(const Complexe& c);

        Complexe& operator+=(const Complexe& c);

        Complexe& operator-=(const Complexe& c);

        Complexe operator+(const Complexe& c);

        Complexe operator-(const Complexe& c);

        bool operator==(const Complexe& c) const;

        bool operator!=(const Complexe& c) const;

        bool operator<(const Complexe& c) const;

        bool operator>(const Complexe& c) const;

        bool operator<=(const Complexe& c) const;

        bool operator>=(const Complexe& c) const;

        Complexe &operator+=(Pfloat d_a);

        Complexe operator+(Pfloat d_a);

        Complexe &operator-=(Pfloat d_b);

        Complexe operator-(Pfloat d_b);

        Complexe &operator*=(Pfloat d_c);

        Complexe operator*(Pfloat d_c);

        Complexe &operator/=(Pfloat d_c);

        Complexe operator/(Pfloat d_c);

        Complexe &operator*=(const Complexe& c);

        Complexe operator*(const Complexe& c);

        Complexe &operator/=(const Complexe& c);

        Complexe operator/(const Complexe& c);

        /// @brief calculate the conjuagte number of current complexe
        /// @return conjugate (a - bi)
        Complexe conjugate() const;

        /// @brief calulates the distance between (0 + 0i) and current complexe
        /// @return module 
        Pfloat abs() const;

        /// @brief calulates the angle between (0 + 0i) and current complexe
        /// @return angle between 0 and 2*pi
        Pfloat arg() const;

        /// @brief calulates the distance between complexe c and current complexe
        /// @param c other complexe
        /// @return distance
        Pfloat distance(const Complexe& c) const;

        /// @brief calculates the distance between two complexes
        /// @param c first complexe
        /// @param d second complexe
        /// @return distance between
        static Pfloat distance(const Complexe& c, const Complexe& d);

        /// @brief translate a complexe by another
        /// @param c translation number
        /// @return true if successful
        bool translate(const Complexe& c);

        bool translate(Pfloat _a, Pfloat _b);

        bool translate(Pfloat _a);

        /// @brief zoom in or out from 0 + 0i
        /// @param zoom zoom value
        /// @return true if successful
        bool dilation(Pfloat zoom);

        /// @brief rotate around 0 + 0i
        /// @param angle rotation angle
        /// @return true if successful
        bool rotate(Pfloat angle);

        /// @brief calculate power of a complexe number
        /// @param exp exponent
        /// @return the complexe calculated
        Complexe operator^(Pfloat exp);

        /// @brief 
        /// @return exponential of the complexe
        Complexe exp();
};

#endif