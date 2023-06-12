#include "Pfloat.hpp"

using namespace std;

int Pfloat::mode = AUTOMATIC; // default mode is automatic mode

Pfloat::Pfloat(){
	precision = STANDARD_PRECISION;
	exponent = 0;
	digits = new LinkedList<int>();
	neg = false;
}

const string Pfloat::toString() const{
	if(digits->size() == 0) return "0.0";
	ostringstream res("");
	if(neg) res << "-";

	if(exponent < -1){// display first zeros if exponent is negative :
		int z = exponent;
		res << "0.";
		while(z++ + 1 < 0) res << "0";
	}else if(exponent == -1) res << "0";

	for(int i = 0 ; i < digits->size() ; i++ ){
		if(exponent == i-1) res << ".";
		res << digits->get(i);
	}

	for(int i = digits->size() ; i <= exponent ; ++i) res << "0"; // add zeros at the end if needed
	return res.str();
}

const string Pfloat::toeString() const{
	if(digits->size() == 0) return "0.0";
	ostringstream res("");
	if(neg) res << "-";
	res << digits->get(0) << ".";
	for(int i = 1; i < digits->size(); ++i) res << digits->get(i);
	if(exponent != 0) res << "e" << exponent;
	return res.str();
}

const string Pfloat::debugToString() const{
	ostringstream res("");
	if(neg) res << "-"; else res << "+";
	res << digits->toString() << "\te = " << exponent << "\tp = " << precision;
	return res.str();
}

Pfloat::Pfloat(long double n) {
	precision = STANDARD_PRECISION;
	if(n < 0) neg = true;
	else neg = false;
	n = neg ? -n : n;
	digits = new LinkedList<int>();
	exponent = 0;
	if(n == 0.0 || n == -0.0) n = 0;
	std::string s = std::to_string(n);

	char* arg_char = (char*)malloc(s.size()*sizeof(char) + 1);
	strcpy(arg_char, s.c_str());
	for(int i = 0; i < (int)s.size(); i++){
		if(arg_char[i] == '.')  exponent = i-1;
		else                    digits->pushTail(arg_char[i] - '0');
	}
	free(arg_char);
	tidy();
}

bool Pfloat::check_exp_string(std::string const str){
	// check first digits :
	size_t pos = str.find('e');
	if(size_t(pos) == std::string::npos) return check_string(str); // no 'e' so, it's a basic checkup
	std::string digits = str.substr(0, pos);
	if(digits.size() == 0){
		throw std::invalid_argument("argument cannot start with 'e'");
		return false;
	}

	if(!check_string(digits)) return false; // check the first part of the string

	std::string exp = str.substr(pos+1);

	if(exp.size() == 0){
		throw std::invalid_argument("argument cannot end with 'e'");
		return false;
	}
	if (exp[0] != '-' && (exp[0] < '0' || exp[0] > '9'))
		throw std::invalid_argument("exponent must be an int composed of digits betweeen 0 and 9, with optionnally a '-' in first position");

	for(int i = 1; i < (int)exp.size(); i++)
		if(exp[i] > '9' || exp[i] < '0'){
			throw std::invalid_argument("exponent must be an integer");
			return false;
		}
	return true;
}

bool Pfloat::check_string(std::string const str){
	if(str.size() == 0){
		throw std::invalid_argument("string argument must be non-empty");
		return false;
	}if(str.size() == 1 && (str[0] == '-' || str[0] == '.' || str[0] == '+')){
		throw std::invalid_argument("if string length is 1, the string must be a digit");
		return false;
	}if(str.size() == 2 && str[0] == '-' && str[1] == '.'){
		throw std::invalid_argument("the string cannot be '-.'");
		return false;
	}

	char*cs = (char*)malloc(str.size() + 1);
	strcpy(cs, str.c_str());

	int point_count = 0;
	for(int i = 0 ; i < (int)str.size() ; ++i){
		if(cs[i] == '.') point_count++;
		else if(cs[i] == '-'){
			if(i != 0){
				free(cs);
				throw std::invalid_argument("the '-' needs to be placed at the first place of the string");
				return false;
			}
		}else if(cs[i] == '+'){
			if(i != 0){
				free(cs);
				throw std::invalid_argument("the '+' needs to be placed at the first place of the string");
				return false;
			}
		}else if((cs[i] < '0' || cs[i] > '9')){
			free(cs);
			throw std::invalid_argument("Provide digits between 0 and 9");
			return false;
		}
		if(point_count > 1){
			free(cs);
			throw std::invalid_argument("Provide max one '.'");
			return false;
		}
	}
	free(cs);
	return true;
}

std::string trim(const std::string& str) {
	size_t first = str.find_first_not_of(" \t\n\r");
	if (first == std::string::npos)
		return "";

	size_t last = str.find_last_not_of(" \t\n\r");
	return str.substr(first, (last - first + 1));
}

Pfloat::Pfloat(const std::string str){
	std::string trimmed_str = trim(str);
	if(!check_exp_string(trimmed_str))
		throw std::invalid_argument("provide a string containing only digits, optionnally one '.' and a '-' in first position");

	precision = STANDARD_PRECISION;
	if(trimmed_str[0] == '-') neg = true; else neg = false;
	if(neg || trimmed_str[0] == '+') trimmed_str = trimmed_str.substr(1); // remove '-' / '+' char

	std::string exp = "0";
	size_t pos = trimmed_str.find('e');
	if(pos != std::string::npos){
		exp = trimmed_str.substr(pos + 1);
		trimmed_str = trimmed_str.substr(0, pos);
	}

	if (trimmed_str.find('.') == std::string::npos) trimmed_str +=  '.';

	digits = new LinkedList<int>();

	char* arg_char = (char*)malloc(trimmed_str.size()*sizeof(char) + 1);
	strcpy(arg_char, trimmed_str.c_str());
	exponent = 0;
	for(int i = 0; i < (int)trimmed_str.size(); i++){
		if(arg_char[i] == '.')  exponent = i-1;
		else                    digits->pushTail(arg_char[i] - '0');
	}
	exponent += std::stol(exp); // add the int value of the exponent
	free(arg_char);
	tidy();
}

bool Pfloat::tidy(){
	if(precision < 1){
		throw std::invalid_argument("precision must be at least 1");
		exit(1);
	}
	// std::cout << "before" << debugToString() << "\n";
	if(digits->size() == 0) return false;

	// check if each slot has a value below 9 :
	for(int i = digits->size() - 1 ; i > 0 ; --i)
		if(digits->get(i) > 9){
			int tmp = digits->get(i) / 10; // get the overflow value
			digits->set(i, digits->get(i) % 10); // keep the last digit
			digits->set(i - 1, tmp + digits->get(i -1)); // add
		}

	// first slot case :
	while(digits->get(0) > 9){
		digits->push(digits->get(0)/ 10);
		digits->set(1, digits->get(1) % 10); // first slot is now slot n°1
		exponent++;
	}


	// check if each slot has a value greater than 0 :
	for(int i = 1 ; i < digits->size() ; ++i)
		while(digits->get(i) < 0){
			digits->set(i, digits->get(i) + 10); // keep the last digit
			digits->set(i - 1, digits->get(i -1) - 1); // add
		}

	// first slot case :
	if(digits->get(0) < 0){
		neg = !neg;
		for(int i = 0; i < digits->size() ; ++i)
			digits->set(i, -digits->get(i));
		tidy();
	}

	// remove leading zeros
	int i = 0;
	while(i < digits->size() && digits->get(i) == 0){
		i++;
		exponent--;
	}
	if(i != 0) for(int j = 0 ; j < i ; j++) digits->pop();

	// remove trailing zeros
	int static_size = digits->size();
	i = static_size - 1;
	while(i >= 0 && digits->get(i) == 0)--i;
	if(i != static_size - 1) for(int j = i ; j < static_size - 1 ; j++) digits->popTail();
	// assert precision is respected (number of digits is not too large)
	if(digits->size() > precision){
		if(digits->get(precision) >= 5)
			digits->set(precision - 1, digits->get(precision - 1) + 1);
		for(int i = digits->size() - 1; i >= precision  ; --i) digits->popTail();
		tidy();
	}
	return true;
}

Pfloat::Pfloat(Pfloat const &other){
	precision = other.precision;
	digits = new LinkedList<int>();
	for(int i = 0; i < other.digits->size(); i++)
		digits->pushTail(other.digits->get(i));
	exponent = other.getExponent();
	neg = other.neg;
	tidy();
}

Pfloat::Pfloat(const Pfloat& other, const int p){
	precision = p;
	digits = new LinkedList<int>();
	for(int i = 0; i < other.digits->size(); i++)
		digits->pushTail(other.digits->get(i));
	exponent = other.getExponent();
	neg = other.neg;
	tidy();
}

Pfloat Pfloat::operator + (const Pfloat& x) const{
	if(x.neg && !neg) return *this - x.abs();
	if(x.neg && neg) return Pfloat(0) - (this->abs() + x.abs());
	if(!x.neg && neg) return x - this->abs();
	// here, both this and x are positive
	// considering 'this' has an exp = e1 and 'x' has an exp = e2. the slots will correspond themselves by an offset of moving left the 'x' tab by e2 - e1
	Pfloat res(x); // copy argument
	int max_t = exponent + 1, max_x = res.getExponent() + 1, min_t = max_t - digits->size(), min_x = max_x - res.digits->size();

	// add enough slots at the beginning of the array :
	for(int i = max_x ; i < max_t ; ++i){
		res.digits->push(0);
		res.exponent++;
	}

	// add enough slots at the end of the array
	for(int i = min_x ; i > min_t ; --i) res.digits->pushTail(0);

	// add digits from 'this' to res :
	for(int i = 0 ; i < digits->size(); ++i)
		res.digits->set(i + res.exponent - exponent, digits->get(i) + res.digits->get(i + res.exponent - exponent));
	res.tidy();
	return res;
}

Pfloat Pfloat::operator - (const Pfloat& x) const{
	if(!neg && x.neg) return *this + x.abs();
	if(neg && x.neg) return x.abs() - this->abs();
	if(neg && !x.neg) return Pfloat(0) - (this->abs() + x);
	// here, both this and x are positive
	Pfloat res(x);
	int max_t = exponent + 1, max_x = res.getExponent() + 1, min_t = max_t - digits->size(), min_x = max_x - res.digits->size();

	for(int i = max_x ; i < max_t ; ++i){
		res.digits->push(0);
		res.exponent++;
	}

	for(int i = min_x   ; i > min_t                         ; --i) res.digits->pushTail(0);
	for(int i = 0       ; i < 0 + res.exponent - exponent   ; ++i) res.digits->set(i, -res.digits->get(i)); // make negative the first numbers because they won't be handled by the loops
	for(int i = 0       ; i < digits->size()                ; ++i) res.digits->set(i + res.exponent - exponent, digits->get(i) - res.digits->get(i + res.exponent - exponent));

	for(int i = digits->size(); i < res.digits->size(); ++i)
		if(i + res.exponent - exponent < res.digits->size()) res.digits->set(i + res.exponent - exponent, 0 - res.digits->get(i + res.exponent - exponent));

	res.tidy();
	return res;
}

Pfloat& Pfloat::operator = (const Pfloat& n) {
	digits->clear();
	// Copy the digits of the other Pfloat to this Pfloat
	for (int i = 0; i < n.digits->size(); i++)  digits->pushTail(n.digits->get(i));
	exponent = n.exponent;
	precision = n.precision; 
	return *this;
}

bool Pfloat::operator == (const Pfloat& x) const{
	if((digits->size() == 0 && x.digits->size() == 0)
	|| (digits->size() == 0 && x.digits->size() == 1 && x.digits->get(0) == 0)
	|| (x.digits->size() == 0 && digits->size() == 1 && digits->get(0) == 0)) return true;

	// copy this and x :
	Pfloat t = *this;
	Pfloat xx = x;
	xx.precision = precision > x.precision ? x.precision : precision; // min precision
	t.precision = xx.precision; // min precision
	// tidy
	t.tidy(); xx.tidy();


	if(t.neg != xx.neg) return false;

	// compare exponents and digits :
	if(t.digits->size() != x.digits->size()) return false;

	for(int i = 0; i < t.digits->size(); ++i) if(t.digits->get(i) != x.digits->get(i)) return false;
	if(t.exponent != x.exponent) return false;
	return true; // all tests passed
}

Pfloat Pfloat::abs() const{
	Pfloat res(*this);
	res.neg = false;
	return res;
}

bool Pfloat::operator < (const Pfloat& x) const {
	if(neg == true && x.neg == false) return true;
	if(neg == false && x.neg == true) return false;
	if(neg == true && x.neg == true) return this->abs() > x.abs();
	if(*this == x) return false;
	if(exponent < x.exponent) return true;
	if(exponent > x.exponent) return false;
	// same exponents // copy this and x :
	Pfloat t = *this, xx = x;
	t.tidy(); xx.tidy(); // tidy
	return t.rec_inf(x, 0);
}

bool Pfloat::rec_inf(const Pfloat b, int index_cmp) const{
	if(digits->size() > index_cmp && b.digits->size() > index_cmp){
		if(digits->get(index_cmp) > b.digits->get(index_cmp)) return false;
		if(digits->get(index_cmp) < b.digits->get(index_cmp)) return true;
		return rec_inf(b, index_cmp + 1); // recursion
	}else if(digits->size() == index_cmp && b.digits->size() > index_cmp) return true;// b is larger
	else if(digits->size() > index_cmp && b.digits->size() == index_cmp) return false;
	else return false; // same size of digits arrays so they are equals
}

Pfloat Pfloat::operator * (const Pfloat& x) const{
	// === quick cases ===
	if(x == Pfloat(0) || *this == Pfloat(0)) return Pfloat(0, x.precision > precision ? precision : x.precision);
	if(x == Pfloat(1)) return Pfloat(*this);
	if(*this == Pfloat(1)) return Pfloat(x);
	if(x == Pfloat(-1)){
		Pfloat r(*this);
		r.neg = !r.neg;
		return r;
	}
	if(*this == Pfloat(-1)){
		Pfloat r(x);
		r.neg = !r.neg;
		return r;
	}
	Pfloat res;
	res.precision = x.precision > precision ? precision : x.precision;
	res.exponent = x.exponent;
	// =============================== add slots to res
	for(int i = 0 ; i < digits->size() + x.digits->size(); ++i) res.digits->push(0);

	// multiply the numbers using this rule : foreach slots of number1, multiply if with the slots of number2 and store the result at slot index : e1 + e2 - slot_n1 - slot_n2
	for(int i = 0 ; i < digits->size(); ++i) for(int j = 0 ; j < x.digits->size() ; ++j)
			// std::cout << "index = " << index << "\t" << res.debugToString() << "\n\t= " << res.digits->get(index) << " + " << digits->get(i) << " * " << x.digits->get(j) << "\n";
			res.digits->set(i + j, res.digits->get(i + j) + digits->get(i) * x.digits->get(j));

	res.digits->reverse();
	// set the exponent of the result
	res.exponent = exponent + x.exponent;
	res.tidy();
	// manage sign :
	if(x.neg == this->neg) res.neg = false;
	else res.neg = true;
	return res;
}

Pfloat Pfloat::pow(const int& n) const{
	if(*this == 1	) return Pfloat(1, precision);
	if(    n == 0 	) return Pfloat(1, precision);
	if(*this == 0	) return Pfloat(0, precision);

	Pfloat res(0, precision + 3), cpy(abs(), precision + 3);

	int p = n > 0 ? n : -n; // get the absolute value.

	res = cpy.pow_rec(p, cpy.precision);
	if(n < 0) res = Pfloat(1, precision + 3) / res;
	
	res.precision = precision;
	res.tidy(); 
	if(neg && n % 2 == 1) res.neg = true;
	return res;
}

Pfloat Pfloat::pow_rec(const int n, const int p) const {
	// quick cases
	if(		n == 0	)	return Pfloat(1	   , p);
	if(		n == 1	) 	return Pfloat(*this, p);
	if(		n == 2	)	return Pfloat(*this, p)*Pfloat(*this, p);
	if(		n == 3	)	return Pfloat(*this, p)*Pfloat(*this, p)*Pfloat(*this, p);
	if( n % 2 == 0	)	return Pfloat(*this, p).pow_rec(n/2 , p).pow_rec(2, p);					 // even
	else	 			return Pfloat(*this, p).pow_rec(n/2 , p).pow_rec(2, p)*Pfloat(*this, p); // odd
	
	
}

Pfloat Pfloat::operator % (const Pfloat& x) const {
	if(this->neg || x.neg || x == 0) throw std::invalid_argument("\% operator works only on positive numbers");
	Pfloat t(*this);
	if(x > t) return t;
	Pfloat y(x);

	long exp_count = 0;
	while(y.exponent + 1 < t.exponent){
		y.exponent++;
		exp_count++;
	}
	while(exp_count >= 0){
		while(t >= y){
			t = t - y; // TODO: replace with -=
		}
		exp_count--;
		y.exponent--;
	}
	t.tidy();
	return t;
}

Pfloat Pfloat::quotient(const Pfloat& x) const{

	if(this->neg || x.neg || x == 0) throw std::invalid_argument("quotient function only works on positive numbers");
	Pfloat t(*this);

	if(x == 1)      return t;
	if(x == *this)  return Pfloat(1);
	if(x > t)       return Pfloat(0);

	Pfloat y    (x);
	Pfloat res  (0);
	Pfloat ten  (10);
	Pfloat tmp  (0);

	t.precision     = x.precision + 2;
	y.precision     = x.precision + 2;
	res.precision   = x.precision + 2;
	ten.precision   = x.precision + 2;

	long exp_count = t.exponent - y.exponent - 1;
	y.exponent += exp_count;

	while(exp_count >= 0){
		while(t > y){
			t = t - y; // TODO: replace with -=
			tmp = ten.pow(exp_count);
			tmp.precision = res.precision; // don't disturb res.precision
			res = res + tmp;
		}
		exp_count--;
		y.exponent--;
	}

	res.precision--;
	return res;
}

Pfloat Pfloat::operator / (const Pfloat& x) const{
	if(x == 0)      throw std::invalid_argument("cannot divide by zero");
	if(x == 1)      return Pfloat(*this);
	if(x == *this)  return Pfloat(1);

	Pfloat to_divide(*this);

	long exp_increase   = to_divide.precision + x.exponent - to_divide.exponent + 2;
	to_divide.exponent += exp_increase;

	Pfloat res(0);
	res = to_divide.abs().quotient(x.abs()); // compute division
	res.exponent -= exp_increase;
	Pfloat mod(0);
	mod = to_divide % res;
	if(mod.digits->size() != 0 && mod.digits->get(0) >= 5) res.digits->set(res.digits->size() - 1, res.digits->get(res.digits->size() - 1) + 1); // round

	res.tidy();
	res.neg = neg != x.neg; // basic negation rule
	return res;
}

bool  Pfloat::set_display(const int x){
	if(x != NORMAL && x != AUTOMATIC && x != SCIENTIFIC && x != DEBUG) return false;
	mode = x;
	return true;
}

std::ostream& operator << (std::ostream& os, const Pfloat& x) {
	switch(x.mode){
		case NORMAL:
			return os << x.toString();
		case SCIENTIFIC:
			return os << x.toeString();
		case DEBUG:
			return os << x.debugToString();
		case AUTOMATIC:
			// if more than 3 trailing zeroes, use 'e' notation
			if(abs(x.exponent) - x.digits->size() >= 3) 	return os << x.toeString();
			else									return os << x.toString();
		default:
			throw std::runtime_error("error on the display mode in Pfloat class");
	}
}

Pfloat Pfloat::sqrt( const Pfloat x ){
	if (x.neg) throw std::runtime_error("Cannot calculate square root of a negative number");
    
	Pfloat cpy = x;
    Pfloat guess = x;
	Pfloat two = 2;
	Pfloat end_signal = 1;

	cpy.precision = x.precision; guess.precision = x.precision;	two.precision = x.precision; end_signal.precision = x.precision;



    // Iterate until the difference between guess^2 and x is within a desired tolerance

	end_signal.exponent = - end_signal.precision;

	std::cout << "p = " << end_signal << "\n";

	std::cout << "\ncpy = " << cpy.debugToString() << "\nguess = " << guess.debugToString() << "\ntwo = " << two.debugToString() << "\nend_signal = " << end_signal.debugToString() << "\n";
	int i = 0;
    while (i++ <= x.precision + 1){
		// std::cout << "loop it \n";
		// std::cout << "\ncpy = " << cpy.debugToString() << "\nguess = " << guess.debugToString() << "\ntwo = " << two.debugToString() << "\nend_signal = " << end_signal.debugToString() << "\n";
		// std::cout << "(guess + cpy).precision : " << (guess + cpy).precision << "\n";
		// std::cout << "(guess + cpy / guess).precision : " << (guess + cpy / guess).precision << "\n";
		// std::cout << "((guess + cpy / guess) / two).precision : " << ((guess + cpy / guess) / two).precision << "\n";

        guess = (guess + cpy / guess) / two;
    } 
	std::cout << "guess: " << guess.debugToString() << std::endl; 
	guess.precision = x.precision;
	guess.tidy(); 
    return guess;
}

// === One-line functions =================================

int 	Pfloat::getExponent	(						) 	const		{return exponent;				}
		Pfloat::~Pfloat		(						)				{delete digits;					}
void 	Pfloat::exp_shift	(const int shift		)				{exponent += shift;				}

Pfloat  Pfloat::operator +  (const long double& x	)	const   	{return (*this) + Pfloat(x);	}
Pfloat  Pfloat::operator +  (const std::string& str	)   const   	{return (*this) + Pfloat(str);	}
Pfloat& Pfloat::operator += (const Pfloat& x		)               {return(*this = *this + x);		}
Pfloat& Pfloat::operator += (const long double& x	)              	{return(*this = *this + x);		}
Pfloat& Pfloat::operator += (const std::string& str	)            	{return(*this = *this + str);	}

Pfloat  Pfloat::operator -  (const long double& x	)   const   	{return (*this) - Pfloat(x);	}
Pfloat  Pfloat::operator -  (const std::string& str	)   const   	{return (*this) - Pfloat(str);	}
Pfloat& Pfloat::operator -= (const Pfloat& x		)               {return(*this = *this - x);		}
Pfloat& Pfloat::operator -= (const long double& x	)              	{return(*this = *this - x);		}
Pfloat& Pfloat::operator -= (const std::string& str	)           	{return(*this = *this - str);	}

Pfloat  Pfloat::operator *  (const long double& x	)   const   	{return (*this) * Pfloat(x);	}
Pfloat  Pfloat::operator *  (const std::string& str	)   const   	{return (*this) * Pfloat(str);	}
Pfloat& Pfloat::operator *= (const Pfloat& x		)               {return(*this = *this * x);		}
Pfloat& Pfloat::operator *= (const long double& x	)              	{return(*this = *this * x);		}
Pfloat& Pfloat::operator *= (const std::string& str	)            	{return(*this = *this * str);	}

Pfloat  Pfloat::operator /  (const long double& x	)   const   	{return (*this) / Pfloat(x);	}
Pfloat  Pfloat::operator /  (const std::string& str	)   const   	{return (*this) / Pfloat(str);	}
Pfloat& Pfloat::operator /= (const Pfloat& x		)               {return(*this = *this / x);		}
Pfloat& Pfloat::operator /= (const long double& x	) 				{return(*this = *this / x);		}
Pfloat& Pfloat::operator /= (const std::string& str	) 				{return(*this = *this / str);	}

Pfloat  Pfloat::operator %  (const long double& x	)   const   	{return (*this) % Pfloat(x);	}
Pfloat  Pfloat::operator %  (const std::string& str	)   const   	{return (*this) % Pfloat(str);	}
Pfloat& Pfloat::operator %= (const Pfloat& x		)               {return(*this = *this % x);		}
Pfloat& Pfloat::operator %= (const long double& x	) 				{return(*this = *this % x);		}
Pfloat& Pfloat::operator %= (const std::string& str	) 				{return(*this = *this % str);	}

Pfloat& Pfloat::operator = 	(const long double& x	)              	{return (*this) = Pfloat(x);	}
Pfloat& Pfloat::operator = 	(const std::string& str	)            	{return (*this) = Pfloat(str);	}

bool 	Pfloat::operator == (const long double& x	)   const   	{return (*this) == Pfloat(x);	}
bool 	Pfloat::operator == (const std::string& str	)   const   	{return (*this) == Pfloat(str);	}

bool 	Pfloat::operator != (const Pfloat& x		)   const   	{return !(*this == x);			}
bool 	Pfloat::operator != (const long double& x	)   const   	{return (*this) != Pfloat(x);	}
bool 	Pfloat::operator != (const std::string& str	)   const   	{return (*this) != Pfloat(str);	}

bool 	Pfloat::operator >  (const Pfloat& x		)   const   	{return !(*this <= x);			}
bool 	Pfloat::operator >  (const long double& x	)   const   	{return (*this) > Pfloat(x);	}
bool 	Pfloat::operator >  (const std::string& str	)   const   	{return (*this) > Pfloat(str);	}

bool 	Pfloat::operator <  (const long double& x	)   const   	{return (*this) < Pfloat(x);	}
bool 	Pfloat::operator <  (const std::string& str	)   const   	{return (*this) < Pfloat(str);	}

bool 	Pfloat::operator >= (const Pfloat& x		)    const		{return !(*this < x);			}
bool 	Pfloat::operator >= (const long double& x	)    const   	{return (*this) >= Pfloat(x);	}
bool 	Pfloat::operator >= (const std::string& str	)    const   	{return (*this) >= Pfloat(str);	}

bool 	Pfloat::operator <= (const Pfloat& x		)    const   	{return (*this < x)||(*this==x);}
bool 	Pfloat::operator <= (const long double& x	)    const   	{return (*this) <= Pfloat(x);	}
bool 	Pfloat::operator <= (const std::string& str	)    const   	{return (*this) <= Pfloat(str);	}