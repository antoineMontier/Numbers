#ifndef COMPLEXE_HPP
#define COMPLEXE_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#define PI 3.141592653589793238462643383279502884197169

using namespace std;

class Complexe{

    private :
        double a, b;

    public:
    
        /// @brief create 0 + 0i
        Complexe();

        /// @brief creates a + bi
        /// @param _a real number
        /// @param _b imaginary number
        Complexe(double _a, double _b);

        /// @brief creates a + 0*i
        /// @param _a real number
        Complexe(double _a);

        /// @brief copy a complexe number
        /// @param c the number to copy
        Complexe(const Complexe& c);

        /// @brief representation of complexe number
        /// @return a complexe number representation " a + bi"
        const string toString() const;

        /// @brief set the real number
        /// @param _a new real number
        void setRe(double _a);

        /// @brief set the imaginary number
        /// @param _b new imaginary number
        void setIm(double _b);

        /// @brief get the real number
        /// @return real number
        double getRe() const;

        /// @brief get the imaginary number
        /// @return imaginary number
        double getIm() const;

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

        Complexe &operator+=(double d_a);

        Complexe operator+(double d_a);

        Complexe &operator-=(double d_b);

        Complexe operator-(double d_b);

        Complexe &operator*=(double d_c);

        Complexe operator*(double d_c);

        Complexe &operator/=(double d_c);

        Complexe operator/(double d_c);

        Complexe &operator*=(const Complexe& c);

        Complexe operator*(const Complexe& c);

        Complexe &operator/=(const Complexe& c);

        Complexe operator/(const Complexe& c);

        friend std::ostream& operator << (std::ostream& os, const Complexe& x);


        /// @brief calculate the conjuagte number of current complexe
        /// @return conjugate (a - bi)
        Complexe conjugate() const;

        /// @brief calulates the distance between (0 + 0i) and current complexe
        /// @return module 
        double abs() const;

        /// @brief calulates the angle between (0 + 0i) and current complexe
        /// @return angle between 0 and 2*pi
        double arg() const;

        /// @brief calulates the distance between complexe c and current complexe
        /// @param c other complexe
        /// @return distance
        double distance(const Complexe& c) const;

        /// @brief calculates the distance between two complexes
        /// @param c first complexe
        /// @param d second complexe
        /// @return distance between
        static double distance(const Complexe& c, const Complexe& d);

        /// @brief translate a complexe by another
        /// @param c translation number
        /// @return true if successful
        bool translate(const Complexe& c);

        bool translate(double _a, double _b);

        bool translate(double _a);

        /// @brief zoom in or out from 0 + 0i
        /// @param zoom zoom value
        /// @return true if successful
        bool dilation(double zoom);

        /// @brief rotate around 0 + 0i
        /// @param angle rotation angle
        /// @return true if successful
        bool rotate(double angle);

        /// @brief calculate power of a complexe number
        /// @param exp exponent
        /// @return the complexe calculated
        Complexe operator^(double exp);

        /// @brief 
        /// @return exponential of the complexe
        Complexe exp();

};

#endif