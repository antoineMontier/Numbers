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

    public:

        BigInt();

        BigInt(int n);

        ~BigInt();

        const string toString() const;
};

#endif