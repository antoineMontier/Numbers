#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "LinkedList.cpp"

#ifndef BIGINT_HPP
#define BIGINT_HPP

using namespace std;

class BigInt{

    private: 

        LinkedList<int>* num;

        /// @brief recuresive function to test if a number is greater than another
        /// @param n number to test
        /// @param index index of the test
        /// @return true or false depending on the number comparison
        bool rec_inf(const BigInt& n, int index) const;

    public:

        BigInt();

        BigInt(int n);

        BigInt(const BigInt& n);

        BigInt(long int n);

        ~BigInt();

        const string toString() const;

        const string debugToString() const;

        BigInt operator + (const BigInt& n) const;
        BigInt operator + (long n) const;

        BigInt operator - (const BigInt& n) const;
        BigInt operator - (long n) const;

        BigInt operator * (const BigInt& n) const;
        BigInt operator * (long n) const;

        /// @brief if a number is less than 0 or greater than 9, change it between 0-9 to fit in the cell and add or subtract to the next cells
        /// @return if changes has been made 
        bool tidy();

        bool operator < (const BigInt& n) const;
        bool operator < (long n) const;

        bool operator == (const BigInt& n) const;
        bool operator == (long n) const;

        bool operator != (const BigInt& n) const; 
        bool operator != (long n) const; 

        bool operator > (const BigInt& n) const;
        bool operator > (long n) const;

        bool operator >= (const BigInt& n) const;
        bool operator >= (long n) const;

        bool operator <=(const BigInt& n) const;
        bool operator <=(long n) const;

        BigInt operator % (const BigInt& n) const;
        BigInt operator % (long n) const;

        BigInt operator / (const BigInt& n) const;
        BigInt operator / (long n) const;

        BigInt& operator = (const BigInt& n);
        BigInt& operator = (long n);

        void operator *= (const BigInt& n);
        void operator *= (long n);

        void operator /= (const BigInt& n);
        void operator /= (long n);

        void operator -= (const BigInt& n);
        void operator -= (long n);

        void operator += (const BigInt& n);
        void operator += (long n);
        
        /// @brief get the factorial of a integer number
        /// @param n number to get factorial
        /// @return factorial result
        static BigInt factorial(long n);
        
        /// @brief fibonnacci value of a specific number
        /// @param n terme to calculate
        /// @return fibonnacci result
        static BigInt fibonnacci(long n);

        /// @brief check if the number is a palidrome (ex : 1536351)
        /// @return true if palidrome, false otherwise
        bool palindrome() const;
        
        BigInt operator ^ (const BigInt& exp) const;
    
        LinkedList<int> * getDigits() const;
};



#endif