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
/*need to compare first 
BigInt BigInt::operator - (const BigInt& n) const{
    BigInt res;
    for (int i = 0; i < std::max(num->size(), n.num->size()); i++){
        if(i < min(num->size(), n.num->size()))
            res.num->push(num->get(i) - n.num->get(i));
        else if(i >= num->size() && i < n.num->size())
            res.num->push(n.num->get(i));
        else if(i >= n.num->size() && i < num->size())
            res.num->push(num->get(i));
        else
            std::cout << " 'operator +' bug" << std::endl;
    }
    res.tidy();
    return res;
}*/


bool BigInt::tidy(){
    bool res = false;
    int tmp = 0;
    for (int i = 0; i < num->size(); i++){
        //std::cout <<"              "<< debugToString() << " i = " << i << std::endl;
        if(num->get(i) >= 10){
            res = true;
            tmp = num->get(i)/10;
            num->set(i, num->get(i) % 10);
            if(i < num->size() - 1)
                num->set(i + 1, num->get(i + 1) + tmp);
            else
                num->pushTail(tmp);
        }
        //std::cout <<"              "<< debugToString() << " i = " << i << std::endl;
    }
    //remove useless 0
    while(num->size() > 0 && num->get(num->size() - 1) == 0)
        num->popTail();
    return res;
}

BigInt BigInt::operator * (const BigInt& n) const{
    BigInt res;
    //add enough digits 
    for (int i = 0; i < num->size() +  n.num->size(); i++)
        res.num->push(0);
    for (int i = 0; i < num->size() ; i++) 
        for (int j = 0; j < n.num->size(); j++){
            //std::cout << num->get(i) << " * " << n.num->get(j) << " * 10^" << i+j << std::endl;
            res.num->set(i + j, res.num->get(i + j) + num->get(i) * n.num->get(j));
        }
    //std::cout << res.debugToString() << std::endl;
    res.tidy();
    return res;
}

