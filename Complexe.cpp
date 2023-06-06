#include "Complexe.hpp"

using namespace std;

Complexe::Complexe(){
    a = 0;
    b = 0;
}

Complexe::Complexe(Pfloat _a, Pfloat _b){
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
                res << "- " << Pfloat(0) - b << "i";
        }if(b == 0)
            res << "0";
    }else if(b == 0){
        if(a > 0)
            res << a;
        if(a < 0)
            res << "-" << Pfloat(0) - a;
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
                res << a << " - " << Pfloat(0) - b << "i";
        }else if(a < 0 && b > 0){
            if(b == 1)
                res <<"-"<< Pfloat(0) - a << " + i";
            else
                res <<"-"<< Pfloat(0) - a << " + " << b << "i";
        }else if(a < 0 && b < 0){
            if(b == -1)
                res <<"-"<< Pfloat(0) - a << " - i";
            else
                res <<"-"<< Pfloat(0) - a << " - " << Pfloat(0) - b << "i";
        }
    }
    return res.str();
}

void Complexe::setRe(Pfloat _a){a = _a;}

void Complexe::setIm(Pfloat _b){b = _b;}

Pfloat Complexe::getRe() const{return a;}

Pfloat Complexe::getIm() const{return b;}

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

Complexe Complexe::operator+(const Complexe& c){
    return Complexe(a + c.a, b + c.b);
}

Complexe Complexe::operator-(const Complexe& c){
    return Complexe(a - c.a, b - c.b);
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


Complexe& Complexe::operator+=(Pfloat d_a){a+=d_a; return *this;}

Complexe& Complexe::operator-=(Pfloat d_a){a-=d_a; return *this;}

Complexe& Complexe::operator*=(Pfloat d_a){a*=d_a; b*=d_a; return *this;}

Complexe& Complexe::operator/=(Pfloat d_a){a/=d_a; b/=d_a; return *this;}

Complexe& Complexe::operator*=(const Complexe& c){
    a = a*c.a - b*c.b;
    b = a*c.b + b*c.a;
    return *this;
}

Complexe Complexe::operator*(const Complexe& c){
    return Complexe(a*c.a - b*c.b, a*c.b + b*c.a);
    }

Complexe& Complexe::operator/=(const Complexe& c){
    if(c.a == 0 && c.b == 0)
        throw std::runtime_error("Division by zero");
    Complexe * res = new Complexe();
    res->a = (c.a*a - c.b*b) / (c.a*c.a + c.b*c.b);
    res->b = (c.a*b + c.b*a) / (c.a*c.a + c.b*c.b);
    return *res;
}

Complexe Complexe::operator/(const Complexe& c) {
    return Complexe((c.a*1.0*a +c.b*1.0*b) / (c.a*1.0*c.a + c.b*1.0*c.b), (c.a*1.0*b - c.b*1.0*a)  / (c.a*1.0*c.a + c.b*1.0*c.b));
}


Complexe Complexe::operator+(Pfloat d_a){
    return Complexe(a + d_a, b);
}

Complexe Complexe::operator-(Pfloat d_b){
    return Complexe(a - d_b, b);
}

Complexe Complexe::operator*(Pfloat d_c){
    return Complexe(a * d_c, b*d_c);
}

Complexe Complexe::operator/(Pfloat d_c){
    if(d_c == 0)
        throw std::runtime_error("Division by zero");
    return Complexe(a / d_c, b / d_c);
}

Complexe Complexe::conjugate() const{return Complexe(a, -b);}


Pfloat Complexe::abs() const {return sqrt(a*a + b*b);}

Pfloat Complexe::arg() const {return atan(b*1.0/a);}

Pfloat Complexe::distance(const Complexe& c) const{return sqrt((c.a - a) * (c.a - a) + (c.b - b) * (c.b - b));}

bool Complexe::translate(const Complexe& c){
    a += c.a;
    b += c.b;
    return true;
}

bool Complexe::translate(Pfloat _a, Pfloat _b){
    a += _a;
    b += _b;
    return true;
}

bool Complexe::translate(Pfloat _a){
    a += _a;
    return true;
}

bool Complexe::dilation(Pfloat zoom){
    if(zoom == 0.0)
        return false;
    a *= zoom;
    b *= zoom;
    return true;
}

bool Complexe::rotate(Pfloat angle){
    Complexe rotation_center(cos(angle), sin(angle));
    (*this) *= rotation_center;
    return true;
}


Complexe Complexe::operator^(Pfloat exp){
    if(exp == 0.0)
        return Complexe(1, 0);
    return Complexe(pow(abs(), exp)*cos(arg() * exp), pow(abs(), exp)*sin(arg() * exp));
}

Complexe Complexe::exp(){
    if(b == 0.0)
        return Complexe(exp10(a), 0);
    return Complexe(exp10(a)*cos(b), exp10(a)*sin(b)); //replace exp10 by exp ?
}

Pfloat Complexe::distance(const Complexe& c, const Complexe& d){
    return sqrt((c.a - d.a)*(c.a - d.a) + (c.b - d.b)*(c.b - d.b));
}
