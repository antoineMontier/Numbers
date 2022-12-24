#include "BigInt.hpp"

using namespace std;

BigInt::BigInt(){
    num = new LinkedList<int>();
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

BigInt::BigInt(long int n){
    num = new LinkedList<int>();
    int num_digits = std::floor(std::log10(n)) + 1;
    while(num_digits > 0){
        num->pushTail(n %10);
        n /= 10;
        num_digits--;
    }
}

BigInt::BigInt(BigInt const& other){
    num = new LinkedList<int>();
    for(int i = 0; i < other.num->size(); i++)
        num->pushTail(other.num->get(i));
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

const string BigInt::debugToString() const {
    ostringstream res;
    res << "size: " << num->size() << "\n";
    for (int i = num->size() -1; i >= 0 ; i--)
        res << "[" << num->get(i) << "]";
    if (num->size() == 0)
        res <<"[" << "0"<<"]";
    return res.str();
}

BigInt BigInt::operator + (const BigInt& n) const{
    BigInt res;
    for (int i = 0; i < std::max(num->size(), n.num->size()); i++){
        if(i < min(num->size(), n.num->size()))
            res.num->push(n.num->get(i) + num->get(i));
        else if(i >= num->size() && i < n.num->size())
            res.num->push(n.num->get(i));
        else if(i >= n.num->size() && i < num->size())
            res.num->push(num->get(i));
        else
            std::cout << " 'operator +' bug" << std::endl;
    }
    res.tidy();
    return res;
}

bool BigInt::tidy(){
    bool res = false;
    int tmp = 0;
    for (int i = 0; i < num->size(); i++){
        if(num->get(i) >= 10){
            res = true;
            tmp = num->get(i) - 10;
            num->set(i, num->get(i) - 10);
            if(i < num->size() - 1)
                num->set(i + 1, num->get(i + 1) + tmp);
            else
                num->push(tmp);
        }
    }
    return res;
}

