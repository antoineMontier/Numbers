#include "BigInt.hpp"

using namespace std;

BigInt::BigInt(){
    num = new LinkedList<int>();
    num->pushTail(0);
}

BigInt::BigInt(int n){
    num = new LinkedList<int>();
    int num_digits = std::floor(std::log10(n)) + 1;
    while(num_digits > 0){
        num->pushTail(n %10);
        n /= 10;
        num_digits--;
    }
}

BigInt::~BigInt(){
    delete num;
}

const string BigInt::toString() const {
    ostringstream res;
    for (int i = num->size() -1; i >= 0 ; i--) 
        res << num->get(i);
    if (num->size() == 0)
        res << "0";
    return res.str();
}

