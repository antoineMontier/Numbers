#include "PComplexe.hpp"

using namespace std;

PComplexe::PComplexe(){
    a = 0;
    b = 0;
}

PComplexe::PComplexe(Pfloat _a, Pfloat _b){
    a = _a;
    b = _b;
}

PComplexe::PComplexe(const PComplexe& c){
    a = c.a;
    b = c.b;
}

const string PComplexe::toString() const
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

void PComplexe::setRe(Pfloat _a){a = _a;}

void PComplexe::setIm(Pfloat _b){b = _b;}

Pfloat PComplexe::getRe() const{return a;}

Pfloat PComplexe::getIm() const{return b;}

PComplexe& PComplexe::operator=(const PComplexe& c){
    a = c.a;
    b = c.b;
    return *this;
}

PComplexe& PComplexe::operator+=(const PComplexe& c){
    a += c.a;
    b += c.b;
    return *this;
}

PComplexe& PComplexe::operator-=(const PComplexe& c){
    a -= c.a;
    b -= c.b;
    return *this;
}

PComplexe PComplexe::operator+(const PComplexe& c){
    return PComplexe(a + c.a, b + c.b);
}

PComplexe PComplexe::operator-(const PComplexe& c){
    return PComplexe(a - c.a, b - c.b);
}

bool PComplexe::operator==(const PComplexe& c) const{return a == c.a && b == c.b;}

bool PComplexe::operator!=(const PComplexe& c) const{return a != c.a && b != c.b;}

bool PComplexe::operator<(const PComplexe& c) const{//lexicographic order
    if (a == c.a)
        return b < c.b;
    return a < c.a;
}

bool PComplexe::operator>(const PComplexe& c) const{//lexicographic order
    if (a == c.a)
        return b > c.b;
    return a > c.a;
}

bool PComplexe::operator<=(const PComplexe& c) const{//lexicographic order
    if (a == c.a)
        return b <= c.b;
    return a <= c.a;
}

bool PComplexe::operator>=(const PComplexe& c) const{//lexicographic order
    if (a == c.a)
        return b >= c.b;
    return a >= c.a;
}


PComplexe& PComplexe::operator+=(Pfloat d_a){a+=d_a; return *this;}

PComplexe& PComplexe::operator-=(Pfloat d_a){a-=d_a; return *this;}

PComplexe& PComplexe::operator*=(Pfloat d_a){a*=d_a; b*=d_a; return *this;}

PComplexe& PComplexe::operator/=(Pfloat d_a){a/=d_a; b/=d_a; return *this;}

PComplexe& PComplexe::operator*=(const PComplexe& c){
    a = a*c.a - b*c.b;
    b = a*c.b + b*c.a;
    return *this;
}

PComplexe PComplexe::operator*(const PComplexe& c){
    return PComplexe(a*c.a - b*c.b, a*c.b + b*c.a);
    }

PComplexe& PComplexe::operator/=(const PComplexe& c){
    if(c.a == 0 && c.b == 0)
        throw std::runtime_error("Division by zero");
    PComplexe * res = new PComplexe();
    res->a = (c.a*a - c.b*b) / (c.a*c.a + c.b*c.b);
    res->b = (c.a*b + c.b*a) / (c.a*c.a + c.b*c.b);
    return *res;
}

PComplexe PComplexe::operator/(const PComplexe& c) {
    return PComplexe((c.a*1.0*a +c.b*1.0*b) / (c.a*1.0*c.a + c.b*1.0*c.b), (c.a*1.0*b - c.b*1.0*a)  / (c.a*1.0*c.a + c.b*1.0*c.b));
}


PComplexe PComplexe::operator+(Pfloat d_a){
    return PComplexe(a + d_a, b);
}

PComplexe PComplexe::operator-(Pfloat d_b){
    return PComplexe(a - d_b, b);
}

PComplexe PComplexe::operator*(Pfloat d_c){
    return PComplexe(a * d_c, b*d_c);
}

PComplexe PComplexe::operator/(Pfloat d_c){
    if(d_c == 0)
        throw std::runtime_error("Division by zero");
    return PComplexe(a / d_c, b / d_c);
}

PComplexe PComplexe::conjugate() const{return PComplexe(a, Pfloat() - b);}

/*
Pfloat PComplexe::abs() const {return sqrt(a*a + b*b);}

Pfloat PComplexe::arg() const {return atan(b*1.0/a);}

Pfloat PComplexe::distance(const PComplexe& c) const{return sqrt((c.a - a) * (c.a - a) + (c.b - b) * (c.b - b));}

bool PComplexe::translate(const PComplexe& c){
    a += c.a;
    b += c.b;
    return true;
}

bool PComplexe::translate(Pfloat _a, Pfloat _b){
    a += _a;
    b += _b;
    return true;
}

bool PComplexe::translate(Pfloat _a){
    a += _a;
    return true;
}

bool PComplexe::dilation(Pfloat zoom){
    if(zoom == 0.0)
        return false;
    a *= zoom;
    b *= zoom;
    return true;
}

bool PComplexe::rotate(Pfloat angle){
    PComplexe rotation_center(cos(angle), sin(angle));
    (*this) *= rotation_center;
    return true;
}


PComplexe PComplexe::operator^(Pfloat exp){
    if(exp == 0.0)
        return PComplexe(1, 0);
    return PComplexe(pow(abs(), exp)*cos(arg() * exp), pow(abs(), exp)*sin(arg() * exp));
}

PComplexe PComplexe::exp(){
    if(b == 0.0)
        return PComplexe(exp10(a), 0);
    return PComplexe(exp10(a)*cos(b), exp10(a)*sin(b)); //replace exp10 by exp ?
}

Pfloat PComplexe::distance(const PComplexe& c, const PComplexe& d){
    return sqrt((c.a - d.a)*(c.a - d.a) + (c.b - d.b)*(c.b - d.b));
}
*/