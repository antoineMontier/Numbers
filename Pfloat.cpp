#include "Pfloat.hpp"

using namespace std;

Pfloat::Pfloat(){
    exponent = 0;
    digits = new LinkedList<int>();
}


Pfloat::~Pfloat(){
    delete digits;
}

Pfloat::Pfloat(long double n) {
    digits = new LinkedList<int>();
    exponent = 0;
    std::string s = std::to_string(n);
    int nbdigts = s.size();
    //for(long unsigned int i = 0; i < s.size(); i++)
        //std::cout << " i =  " << i << " c = " << s.at(i) << std::endl;
    
    if(s.find(".") != std::string::npos){//if there is a dot in the string
        nbdigts--;
        exponent = s.find(".");
        //std::cout << exponent << "   " << s.at(exponent) << std::endl;
        s.erase(exponent, 1);
    }else
        exponent = 0; //int number
    // add each number in the linked list
    //std::cout << "--------------------" << std::endl;
    long int number_no_dot = atoi(&(s.at(0)));
    while(number_no_dot > 0){
        digits->push(number_no_dot %10);
        number_no_dot /= 10;
    }
    tidy();



    /*std::cout << n << std::endl;
    long double decimalp = n;
    long double intp;

    do {
        decimalp = std::modf(n, &intp);
        std::cout << "d  = " << decimalp << "  \tint = " << intp << std::endl;
        n *= 10;
        exponent--;
    } while (decimalp > 0);
    int nn = std::nearbyint(intp);
    std::cout << "\n\n" << nn << "\t" << intp << std::endl;
    int num_digits = std::floor(std::log10(n)) + 1;
    while(num_digits > 0){
        digits->push(nn %10);
        nn /= 10;
        num_digits--;
    }*/
}

Pfloat::Pfloat(const std::string& str){
    digits = new LinkedList<int>();
    std::string s = str;
    int nbdigts = s.size();
    //std::cout << "1" << std::endl;
    //for(long unsigned int i = 0; i < s.size(); i++)
        //std::cout << " i =  " << i << " c = " << s.at(i) << std::endl;
    
    if(s.find(".") != std::string::npos){//if there is a dot in the string
        nbdigts--;
        exponent = s.find(".");
        //std::cout << exponent << "   " << s.at(exponent) << std::endl;
        s.erase(exponent, 1);
    }else
        exponent = 0; //int number
    //std::cout << "2" << std::endl;

    // add each number in the linked list
    //std::cout << "--------------------" << std::endl;
    long int number_no_dot = atoi(&(s.at(0)));
    //std::cout << "3" << "\t"<<number_no_dot<< std::endl;

    while(number_no_dot > 0){
        //std::cout << "\t"<<number_no_dot<< std::endl;
        digits->push(number_no_dot %10);
      //  std::cout << "pushed"<< std::endl;
        number_no_dot /= 10;
    }
    //std::cout << "4" << std::endl;
    tidy();
}


const string Pfloat::toString() const{
    ostringstream res("");
    for(int i = 0 ; i < digits->size() ; i++ ){
        if(exponent == i) res << ".";
        res << digits->get(i);
    }
    return res.str();
}

const string Pfloat::debugToString() const{
    return digits->toString();
}

bool Pfloat::tidy(){
    bool res = false;
    int tmp = 0;
    for(int i = digits->size() - 2; i >= 0 ; i--)
        if(digits->get(i) < 0){
            digits->set(i, 10 + digits->get(i));
            digits->set(i + 1, digits->get(i + 1) - 1);
        } 
    for (int i = 0; i < digits->size(); i++){
        //std::cout <<"              "<< debugToString() << " i = " << i << std::endl;
        if(digits->get(i) >= 10){
            res = true;
            tmp = digits->get(i)/10;
            digits->set(i, digits->get(i) % 10);
            if(i < digits->size() - 1)
                digits->set(i + 1, digits->get(i + 1) + tmp);
            else
                digits->pushTail(tmp);
        }
    }
    //remove useless 0
    while(digits->size() > 0 && digits->get(digits->size() - 1) == 0)
        digits->popTail();
    return res;
}

