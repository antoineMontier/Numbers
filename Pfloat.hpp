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

// === display modes ===
#define AUTOMATIC   (-1254)
#define NORMAL      (-7273)
#define SCIENTIFIC  (+5828)
#define DEBUG       (-9827)

using namespace std;

class Pfloat{ 

private:

    static int mode;

    LinkedList<int>*    digits;

    /// @brief digits*10^exponent
    long                exponent;

    /// @brief tells whether or not the given Pfloat object is negative
    bool                neg;

    /// @brief max number of digits
    int                 precision;



    static bool check_string(std::string const str);

    static bool check_exp_string(std::string const str);


    /// @brief standard toString function
    /// @return string with this format : '-0.000123'
    const string toString(      ) const;

    /// @brief toString function with this format : xxxeXXX
    /// @return string representation of the Pfloat object
    const string toeString(     ) const;

    /// @brief toString function with this format : +/- [x, x, x, x] e = X
    /// @return 
    const string debugToString( ) const;


    /// @brief we assume the exponents of the two Pfloats are the same and they are both tydied
    /// @return true if b is greater than this
    bool    rec_inf     (const Pfloat b, int index_cmp  ) const;

    /// @brief divides a Pfloat object by another
    /// @param x divisor
    /// @return Integer Pfloat object
    Pfloat  quotient    (const Pfloat& x                ) const;

	/// @brief 
	/// @param x POSITIVE INTEGER ONLY
	/// @return 
	Pfloat  pow_rec     (const int x, const int p       ) const;

	        Pfloat      (const Pfloat& n, const int p   );

public:

    /// @brief gets the absolute value of a Pfloat
    /// @return the copied Pfloat object non negative
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

    /// @brief gets the exponent of the Pfloat (debug purposes)
    /// @return the exponent
    int getExponent() const;

    friend std::ostream& operator<<(std::ostream& os, const Pfloat& x);

    /// @brief powers the Pfloat object
    /// @param x the power of the Pfloat 
    /// @return new Pfloat result
    Pfloat  pow(const int& x) const;

    /// @brief tidy up the number
    /// @return true if successful
    bool    tidy();

    /// @brief increase or decrease the exponent of the Pfloat object
    /// @param shift positive integer for increase, negative integer for decrease
    void    exp_shift(const int shift);

    /// @brief sets the display mode : NORMAL : 0.000125 | SCIENTIFIC : 1.25e-4 | DEBUG : +[1, 2, 5] e = -4 | AUTOMATIC : switches between NORMAL and SCIENTIFIC
    /// @param display_mode NORMAL | SCIENTIFIC | DEBUG | AUTOMATIC
    /// @return if the displaye has been set or not. If not, be sure to enter one of the 4 types
    static  bool set_display (const int display_mode  );

    Pfloat  operator -  (const Pfloat& x        ) const;
    Pfloat  operator -  (const long double& x   ) const;
    Pfloat  operator -  (const std::string& str ) const;
    Pfloat& operator -= (const Pfloat& x        );
    Pfloat& operator -= (const long double& x   );
    Pfloat& operator -= (const std::string& str );

    Pfloat  operator +  (const Pfloat& x 		) const;
    Pfloat  operator +  (const long double& x   ) const;
    Pfloat  operator +  (const std::string& str ) const;
    Pfloat& operator += (const Pfloat& x        );
    Pfloat& operator += (const long double& x   );
    Pfloat& operator += (const std::string& str );

    Pfloat  operator *  (const Pfloat& x        ) const;
    Pfloat  operator *  (const long double& x   ) const;
    Pfloat  operator *  (const std::string& str ) const;
    Pfloat& operator *= (const Pfloat& x        );
    Pfloat& operator *= (const long double& x   );
    Pfloat& operator *= (const std::string& str );

    Pfloat  operator /  (const Pfloat& x        ) const;
    Pfloat  operator /  (const long double& x   ) const;
    Pfloat  operator /  (const std::string& str ) const;
    Pfloat& operator /= (const Pfloat& x        );
    Pfloat& operator /= (const long double& x   );
    Pfloat& operator /= (const std::string& str );

    Pfloat  operator %  (const Pfloat& x        ) const;
    Pfloat  operator %  (const long double& x   ) const;
    Pfloat  operator %  (const std::string& str ) const;
    Pfloat& operator %= (const Pfloat& x        );
    Pfloat& operator %= (const long double& x   );
    Pfloat& operator %= (const std::string& str );

    Pfloat& operator =  (const Pfloat& n        );
    Pfloat& operator =  (const long double& n   );
    Pfloat& operator =  (const std::string& str );

    bool    operator == (const Pfloat& x        ) const;
    bool    operator == (const long double& x   ) const;
    bool    operator == (const std::string& str ) const;

    bool    operator != (const Pfloat& x        ) const;
    bool    operator != (const long double& x   ) const;
    bool    operator != (const std::string& str ) const;

    bool    operator <  (const Pfloat& x        ) const;
    bool    operator <  (const long double& x   ) const;
    bool    operator <  (const std::string& str ) const;

    bool    operator <= (const Pfloat& x        ) const;
    bool    operator <= (const long double& x   ) const;
    bool    operator <= (const std::string& str ) const;

    bool    operator >  (const Pfloat& x        ) const;
    bool    operator >  (const long double& x   ) const;
    bool    operator >  (const std::string& str ) const;

    bool    operator >= (const Pfloat& x        ) const;
    bool    operator >= (const long double& x   ) const;
    bool    operator >= (const std::string& str ) const;
};

#endif