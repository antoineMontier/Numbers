#ifndef PCOMPLEXE_HPP
#define PCOMPLEXE_HPP

#include "Pfloat.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#define PI 3.141592653589793238462643383279502884197169

using namespace std;

class PComplexe{
    private :
        Pfloat a, b;

    public:
    
        /// @brief create 0 + 0i
        PComplexe();

        /// @brief create a + bi
        /// @param _a real number
        /// @param _b imaginary number
        PComplexe(Pfloat _a, Pfloat _b);

        /// @brief copy a precise complexe number
        /// @param c the number to copy
        PComplexe(const PComplexe& c);

        /// @brief representation of precise complexe number
        /// @return a precise complexe number representation " a + bi"
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

        PComplexe& operator=(const PComplexe& c);

        PComplexe& operator+=(const PComplexe& c);

        PComplexe& operator-=(const PComplexe& c);

        PComplexe operator+(const PComplexe& c);

        PComplexe operator-(const PComplexe& c);

        bool operator==(const PComplexe& c) const;

        bool operator!=(const PComplexe& c) const;

        bool operator<(const PComplexe& c) const;

        bool operator>(const PComplexe& c) const;

        bool operator<=(const PComplexe& c) const;

        bool operator>=(const PComplexe& c) const;

        PComplexe &operator+=(Pfloat d_a);

        PComplexe operator+(Pfloat d_a);

        PComplexe &operator-=(Pfloat d_b);

        PComplexe operator-(Pfloat d_b);

        PComplexe &operator*=(Pfloat d_c);

        PComplexe operator*(Pfloat d_c);

        PComplexe &operator/=(Pfloat d_c);

        PComplexe operator/(Pfloat d_c);

        PComplexe &operator*=(const PComplexe& c);

        PComplexe operator*(const PComplexe& c);

        PComplexe &operator/=(const PComplexe& c);

        PComplexe operator/(const PComplexe& c);

        /// @brief calculate the conjuagte number of current precise complexe
        /// @return conjugate (a - bi)
        PComplexe conjugate() const;

        /// @brief calulates the distance between (0 + 0i) and current precise complexe
        /// @return module 
        Pfloat abs() const;

        /// @brief calulates the angle between (0 + 0i) and current precise complexe
        /// @return angle between 0 and 2*pi
        Pfloat arg() const;

        /// @brief calulates the distance between precise complexe c and current precise complexe
        /// @param c other precise complexe
        /// @return distance
        Pfloat distance(const PComplexe& c) const;

        /// @brief calculates the distance between two precise complexes
        /// @param c first precise complexe
        /// @param d second precise complexe
        /// @return distance between
        static Pfloat distance(const PComplexe& c, const PComplexe& d);

        /// @brief translate a precise complexe by another
        /// @param c translation number
        /// @return true if successful
        bool translate(const PComplexe& c);

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

        /// @brief calculate power of a precise complexe number
        /// @param exp exponent
        /// @return the precise complexe calculated
        PComplexe operator^(Pfloat exp);

        /// @brief 
        /// @return exponential of the precise complexe
        PComplexe exp();
};

#endif