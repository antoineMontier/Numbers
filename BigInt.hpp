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

        BigInt operator - (const BigInt& n) const;

        BigInt operator * (const BigInt& n) const;

        bool tidy();

        bool operator < (const BigInt& n) const;

        bool operator == (const BigInt& n) const;

        bool operator != (const BigInt& n) const; 

        bool operator > (const BigInt& n) const;

        bool operator >= (const BigInt& n) const;

        bool operator <=(const BigInt& n) const;

        BigInt operator % (const BigInt& n) const;

        BigInt operator / (const BigInt& n) const;

        BigInt& operator = (const BigInt& n);

        void operator *= (const BigInt& n);
        void operator *= (long n);
        void operator /= (const BigInt& n);
        void operator /= (long n);
        void operator -= (const BigInt& n);
        void operator -= (long n);
        void operator += (const BigInt& n);
        void operator += (long n);};

#endif