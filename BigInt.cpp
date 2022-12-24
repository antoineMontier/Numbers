#include "BigInt.hpp"

using namespace std;

BigInt::BigInt(){
    num = new LinkedList<int>();
    num->pushTail(0);
}

BigInt::BigInt(int n){
    num = new LinkedList<int>();
    num->pushTail(n);
}

BigInt::~BigInt(){
    delete num;
}