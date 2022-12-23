#include "Complexe.hpp"

using namespace std;

Complexe::Complexe(){
    a = 0;
    b = 0;
}

Complexe::Complexe(double _a, double _b){
    a = _a;
    b = _b;
}

Complexe::Complexe(const Complexe& c){
    a = c.a;
    b = c.b;
}

const string Complexe::toString() const
{
    ostringstream res;
    if(a == 0){
        if(b > 0){
            if(b == 1)
                res << "i";
            else
                res << b << "i";
        }if(b < 0){
            if(b == -1)
                res << "- i";
            else
                res << "- " << -b << "i";
        }if(b == 0)
            res << "0";
    }else if(b == 0){
        if(a > 0)
            res << a;
        if(a < 0)
            res << "-" << -a;
    }else{// a!=0 && b != 0
        if(a > 0 && b > 0){
            if(b == 1)
                res << a << " + i";
            else
                res << a << " + " << b << "i";
        }else if(a > 0 && b < 0){
            if(b == -1)
                res << a << " - i";
            else
                res << a << " - " << -b << "i";
        }else if(a < 0 && b > 0){
            if(b == 1)
                res <<"-"<< -a << " + i";
            else
                res <<"-"<< -a << " + " << b << "i";
        }else if(a < 0 && b < 0){
            if(b == -1)
                res <<"-"<< -a << " - i";
            else
                res <<"-"<< -a << " - " << -b << "i";
        }
    }
    return res.str();
}

void Complexe::setRe(double _a){a = _a;}

void Complexe::setIm(double _b){b = _b;}

double Complexe::getRe() const{return a;}

double Complexe::getIm() const{return b;}

Complexe& Complexe::operator=(const Complexe& c){
    a = c.a;
    b = c.b;
    return *this;
}

Complexe& Complexe::operator+=(const Complexe& c){
    a += c.a;
    b += c.b;
    return *this;
}

Complexe& Complexe::operator-=(const Complexe& c){
    a -= c.a;
    b -= c.b;
    return *this;
}

Complexe& Complexe::operator+(const Complexe& c){
    Complexe *res = new Complexe(*this);
    res->a += c.a;
    res->b += c.b;
    return *res;
}

Complexe& Complexe::operator-(const Complexe& c){
    Complexe *res = new Complexe(*this);
    res->a -= c.a;
    res->b -= c.b;
    return *res;
}

bool Complexe::operator==(const Complexe& c) const{return a == c.a && b == c.b;}

bool Complexe::operator!=(const Complexe& c) const{return a != c.a && b != c.b;}

bool Complexe::operator<(const Complexe& c) const{//lexicographic order
    if (a == c.a)
        return b < c.b;
    return a < c.a;
}

bool Complexe::operator>(const Complexe& c) const{//lexicographic order
    if (a == c.a)
        return b > c.b;
    return a > c.a;
}

bool Complexe::operator<=(const Complexe& c) const{//lexicographic order
    if (a == c.a)
        return b <= c.b;
    return a <= c.a;
}

bool Complexe::operator>=(const Complexe& c) const{//lexicographic order
    if (a == c.a)
        return b >= c.b;
    return a >= c.a;
}


Complexe& Complexe::operator+=(double d_a){a+=d_a; return *this;}

Complexe& Complexe::operator-=(double d_a){a-=d_a; return *this;}

Complexe& Complexe::operator*=(double d_a){a*=d_a; b*=d_a; return *this;}

Complexe& Complexe::operator/=(double d_a){a/=d_a; b/=d_a; return *this;}

Complexe& Complexe::operator*=(const Complexe& c){
    a = a*c.a - b*c.b;
    b = a*c.b + b*c.a;
    return *this;
}

Complexe& Complexe::operator*(const Complexe& c){
    Complexe * res = new Complexe();
    res->a = a*c.a - b*c.b;
    res->b = a*c.b + b*c.a;
    return *res;
}

Complexe& Complexe::operator/=(const Complexe& c){
    if(c.a == 0 && c.b == 0)
        throw std::runtime_error("Division by zero");
    Complexe * res = new Complexe();
    res->a = (c.a*a - c.b*b) / (c.a*c.a + c.b*c.b);
    res->b = (c.a*b + c.b*a) / (c.a*c.a + c.b*c.b);
    return *res;
}

Complexe& Complexe::operator/(const Complexe& c) {
    Complexe* res = new Complexe(1, 0);
    if(c.b == b && c.a == a)
        return *res;
    res->a = (c.a*1.0*a +c.b*1.0*b) / (c.a*1.0*c.a + c.b*1.0*c.b);
    res->b = (c.a*1.0*b - c.b*1.0*a)  / (c.a*1.0*c.a + c.b*1.0*c.b);
    return *res;
}


Complexe& Complexe::operator+(double d_a){
    Complexe * res = new Complexe(*this);
    res->a += d_a;
    return *res;
}

Complexe& Complexe::operator-(double d_b){
    Complexe * res = new Complexe(*this);
    res->a -= d_b;
    return *res;
}

Complexe& Complexe::operator*(double d_c){
    Complexe * res = new Complexe(*this);
    res->a *= d_c;
    res->b *= d_c;
    return *res;
}

Complexe& Complexe::operator/(double d_c){
    if(d_c == 0)
        throw std::runtime_error("Division by zero");
    Complexe * res = new Complexe(*this);
    res->a /= d_c;
    res->b /= d_c;
    return *res;
}

Complexe Complexe::conjugate() const{return Complexe(a, -b);}


double Complexe::abs() const {return sqrt(a*a + b*b);}

double Complexe::arg() const {return atan(b*1.0/a);}

double Complexe::distance(const Complexe& c) const{return sqrt((c.a - a) * (c.a - a) + (c.b - b) * (c.b - b));}

bool Complexe::translate(const Complexe& c){
    a += c.a;
    b += c.b;
    return true;
}

bool Complexe::translate(double _a, double _b){
    a += _a;
    b += _b;
    return true;
}

bool Complexe::translate(double _a){
    a += _a;
    return true;
}

bool Complexe::dilation(double zoom){
    if(zoom == 0.0)
        return false;
    a *= zoom;
    b *= zoom;
    return true;
}

bool Complexe::rotate(double angle){
    Complexe rotation_center(cos(angle), sin(angle));
    (*this) *= rotation_center;
    return true;
}
