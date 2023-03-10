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
    tidy();
}

BigInt::BigInt(long int n){
    num = new LinkedList<int>();
    int num_digits = std::floor(std::log10(n)) + 1;
    while(num_digits > 0){
        num->pushTail(n %10);
        n /= 10;
        num_digits--;
    }
    tidy();
}

BigInt::BigInt(BigInt const& other){
    num = new LinkedList<int>();
    for(int i = 0; i < other.num->size(); i++)
        num->pushTail(other.num->get(i));
    tidy();
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
            res.num->pushTail(n.num->get(i) + num->get(i));
        else if(i >= num->size() && i < n.num->size())
            res.num->pushTail(n.num->get(i));
        else if(i >= n.num->size() && i < num->size())
            res.num->pushTail(num->get(i));
        else
            throw std::runtime_error("BigInt::operator + bug");
    }
    res.tidy();
    return res;
}
BigInt BigInt::operator +(long n) const{ return (*this) + BigInt(n); }


BigInt BigInt::operator - (const BigInt& n) const{
    BigInt res;
    if(n >= *this) return BigInt(0);
    for (int i = 0; i <= std::max(num->size(), n.num->size()); i++) // add enough space
        res.num->pushTail(0);
    for (int i = 0; i < num->size(); i++)
        res.num->set(i, num->get(i));
    for (int i = 0; i < n.num->size(); i++)
        res.num->set(i, res.num->get(i) - n.num->get(i));

    res.tidy();
    return res;
}
BigInt BigInt::operator -(long n) const{ return (*this) - BigInt(n); }


bool BigInt::tidy(){
    bool res = false;
    int tmp = 0;
    for(int i = num->size() - 2; i >= 0 ; i--)
        if(num->get(i) < 0){
            num->set(i, 10 + num->get(i));
            num->set(i + 1, num->get(i + 1) - 1);
        } 
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
BigInt BigInt::operator *(long n) const{ return (*this) * BigInt(n); }

bool BigInt::operator < (const BigInt& n) const{
    if(*this == n) return false;
    if(num->size() < n.num->size())return true;
    if(num->size() > n.num->size())return false;

    return rec_inf(n, num->size() - 1);
}
bool BigInt::operator < (long n) const{ return (*this) < BigInt(n); }


bool BigInt::rec_inf(const BigInt& n, int index) const{
    //std::cout << "comparing " << num->get(index) << " to " << n.num->get(index) << std::endl;
    if(index < 0 || index >= num->size())
        return false;
    if(num->get(index) < n.num->get(index))
        return true;
    if(num->get(index) > n.num->get(index))
        return false;
    return rec_inf(n, index - 1);
}

bool BigInt::operator == (const BigInt& n) const{
    if(num->size()!= n.num->size())
        return false;
    for(int i = 0; i < num->size(); i++)
        if(num->get(i)!= n.num->get(i))
            return false;
    return true;
}
bool BigInt::operator == (long n) const{ return (*this) == BigInt(n); }


bool BigInt::operator != (const BigInt& n) const{
    if(num->size() != n.num->size())
        return true;
    for(int i = 0; i < num->size(); i++)
        if(num->get(i) != n.num->get(i))
            return true;
    return false;
}
bool BigInt::operator != (long n) const{ return (*this) != BigInt(n); }


bool BigInt::operator > (const BigInt& n) const{return !(*this < n) && *this != n;}
bool BigInt::operator > (long n) const{ return (*this) > BigInt(n); }

bool BigInt::operator >= (const BigInt& n) const{return !(*this < n) || (*this == n);}
bool BigInt::operator >= (long n) const{ return (*this) >= BigInt(n); }

bool BigInt::operator <=(const BigInt& n) const{return *this < n || *this == n;}
bool BigInt::operator <= (long n) const{ return (*this) <= BigInt(n); }


BigInt BigInt::operator / (const BigInt& n) const{
    if( n > *this ) return BigInt(0);
    if( n == *this ) return BigInt(1);
    //std::cout << this->toString() << "  /  " << n.toString() << std::endl;
    BigInt res(0);
    BigInt copy(*this);
    while(copy >= n){
        //std::cout << "iteration = " << res.toString() <<"   res = " << copy.toString() <<  std::endl;
        copy = copy - n;
        res = (res + BigInt(1));
    }
    return res;
}
BigInt BigInt::operator / (long n) const{ return (*this) / BigInt(n); }


BigInt& BigInt::operator=(const BigInt& n) {
    // Clear the current digits of this BigInt
    num->clear();

    // Copy the digits of the other BigInt to this BigInt
    for (int i = 0; i < n.num->size(); i++) {
        num->pushTail(n.num->get(i));
    }

    return *this;
}
BigInt& BigInt::operator = (long n) { return ((*this) = BigInt(n)); }


BigInt BigInt::operator % (const BigInt& n) const{
    if( n <= 0 )
        return BigInt(0);
    BigInt copy(*this);
    while(copy >= n)
        copy = copy - n;
    return copy;
}

void BigInt::operator *= (const BigInt& n){*this = ((*this) * n);}
void BigInt::operator *= (long n){*this = ((*this) * BigInt(n));}

void BigInt::operator /= (const BigInt& n){*this = ((*this) / n);}
void BigInt::operator /= (long n){*this = ((*this) / BigInt(n));}

void BigInt::operator += (const BigInt& n){*this = ((*this) + n);}
void BigInt::operator += (long n){*this = ((*this) + BigInt(n));}

void BigInt::operator -= (const BigInt& n){*this = ((*this) - n);}
void BigInt::operator -= (long n){*this = ((*this) - BigInt(n));}

BigInt BigInt::factorial(long n){
    if(n < 2)
        return BigInt(1);
    return BigInt(n) * factorial(n - 1);
}

BigInt BigInt::fibonnacci(long n){
    if(n == 0) return BigInt(0);
    if(n <= 2) return BigInt(1);

    BigInt a(0), b(1), c(1);
    for(long i=1; i<n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

bool BigInt::palindrome() const{
    // Compare the digits from left to right and from right to left
    for (int i = 0; i < num->size() / 2; i++) {
        if (num->get(i) != num->get(num->size() - 1 - i)) return false;
    }
    return true;
}

BigInt BigInt::operator ^ (const BigInt& exp) const{
    if(exp == 0) return BigInt(1);
    if(exp == 1) return BigInt(*this);
    BigInt result(1);
    for(BigInt k(0) ; k < exp ; k += 1)
        result *= *this;
    return result;
}

LinkedList<int> * BigInt::getDigits() const{
    return num;
}