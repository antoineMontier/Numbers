#include <iostream>
#include <assert.h>
#include "Complexe.hpp"
#include "Pfloat.hpp"

int main(){

    Pfloat a(" 3e2 ");
    Pfloat b(" 4 ");
    std::cout << "a = " << a.toString() << "\nb = " << b.toString() << std::endl;

    std::cout << "a / b = " << (a / b).toString() << std::endl;


    /*
    // === == tests
    assert(Pfloat("2") == Pfloat(2.000000000));
    assert(Pfloat("0") == Pfloat());
    assert(Pfloat() == Pfloat());
    assert(Pfloat() == Pfloat(0));
    assert(Pfloat("0") == Pfloat(-0.0));
    assert(Pfloat("2") == 2.000000000);
    assert(Pfloat("0") == 0);
    assert(Pfloat() == 0);
    assert(Pfloat() == 0);
    assert(Pfloat("0") == -0.0);
    // === != tests
    assert(Pfloat() != Pfloat(1));
    assert(Pfloat(11) != Pfloat(1.1));
    assert(Pfloat(2) + Pfloat(22) != Pfloat());
    assert(Pfloat() != 1);
    assert(Pfloat(11) != 1.1);
    assert(Pfloat(2) + 22 != 0);
    // === + tests
    assert(Pfloat(2) + Pfloat(2) == Pfloat(4));
    assert(Pfloat("0") + Pfloat(2) == Pfloat(2));
    assert(Pfloat(-5.22) + Pfloat("1.5") == Pfloat(-3.72));
    assert(Pfloat("1.999998") + Pfloat("2e-6") == Pfloat(2));
    assert(Pfloat(-5.23) + Pfloat(1.5) == Pfloat(-3.73));
    assert(Pfloat(5.23) + Pfloat(-1.5) == Pfloat("3.73"));
    assert(Pfloat("3.33") + Pfloat(-1.5) == Pfloat(1.83));
    assert(Pfloat(-2.2) + Pfloat("-3.3") == Pfloat(-5.5));
    assert(Pfloat(78.985) + Pfloat(-8745.5) == Pfloat(-8666.515));
    assert(Pfloat("00000e9") - "-0000" == Pfloat(0));
    assert(Pfloat(4.23) - Pfloat(0.0025) == Pfloat("4.2275"));
    assert(Pfloat(-4.23) - "0.0025" == Pfloat(-4.2325));
    assert(Pfloat("0.0025e0") - Pfloat(4.23) == Pfloat(-4.2275));
    assert(Pfloat(2) + 2 == 4);
    assert(Pfloat(0) + 2 == 2);
    assert(Pfloat(-5.22) + 1.5 == -3.72);
    assert(Pfloat("1.999998") + 0.000002 == 2);
    assert(Pfloat(-5.23) + 1.5 == -3.73);
    assert(Pfloat("5.23") + -1.5 == 3.73);
    assert(Pfloat(3.33) + -1.5 == 1.83);
    assert(Pfloat(-2.2) + -3.3 == -5.5);
    assert(Pfloat(78.985) + -8745.5 == -8666.515);
    assert(Pfloat(-00000) - -0000 == 0);
    assert(Pfloat(4.23) - 0.0025 == 4.2275);
    assert(Pfloat(-4.23) - 0.0025 == -4.2325);
    assert(Pfloat(0.0025) - 4.23 == -4.2275);
    // === - tests
    assert(Pfloat(54321.23456) - "12345.67891" == Pfloat(41975.55565));
    assert(Pfloat(3.3) - Pfloat(1.5) == Pfloat(1.8));
    assert(Pfloat(1.5) - Pfloat(3.3) == Pfloat(-1.8));
    assert(Pfloat("-3.3") - Pfloat(1.5) == Pfloat(-4.8));
    assert(Pfloat(-1.5) - Pfloat(-3.3) == Pfloat(1.8));
    assert(Pfloat(54321.23456) - (12345.67891) == "41975.55565");
    assert(Pfloat(3.3) - (1.5) == (1.8));
    assert(Pfloat(1.5) - (3.3) == (-1.8));
    assert(Pfloat(-3.3) - (1.5) == (-4.8));
    assert(Pfloat(-1.5) - (-3.3) == (1.8));
    // === '<' '>' '<=' '>=' tests with +
    assert(Pfloat(0) < Pfloat(1));
    assert(Pfloat(0) < Pfloat(0.123));
    assert(Pfloat(0) < Pfloat(0.01));
    assert(Pfloat(1) < Pfloat(1.1));
    assert(Pfloat(1) < Pfloat(1.01));
    assert(Pfloat(.02) < Pfloat(.03));
    assert(!(Pfloat(.2) < Pfloat(.03)));
    assert(Pfloat(".2222222") < Pfloat(.3));
    assert(!(Pfloat(.12345) < Pfloat(.123450)));
    assert(Pfloat(.12345) < Pfloat(".123451"));
    assert(Pfloat(1.23) > Pfloat(1.22));
    assert(Pfloat("90e-2") <= Pfloat(0.9));
    assert(Pfloat(0.1) >= Pfloat(0.05));
    assert(!(Pfloat("5e-1") < Pfloat(0.5)));
    assert(!(Pfloat(0.1) > Pfloat(0.2)));
    assert(!(Pfloat(2.0) <= Pfloat(1.5)));
    assert(!(Pfloat(0.3) >= Pfloat(0.4)));
    assert(Pfloat("0.00001") < Pfloat(0.0001));
    assert(Pfloat(100000) > Pfloat(10000));
    assert(Pfloat(0.9999) <= Pfloat(1.0));
    assert(Pfloat(0.9999) >= Pfloat(0.999));
    assert(!(Pfloat(0.5) < Pfloat(0.3)));
    assert(!(Pfloat(0.1) > Pfloat(0.1)));
    assert(!(Pfloat(2.0) <= Pfloat(1.5)));
    assert(!(Pfloat(0.4) >= Pfloat(0.5)));
    // === '<' '>' '<=' '>=' tests with -
    assert(Pfloat(-0) > Pfloat(-1));
    assert(Pfloat(-0) > Pfloat("-0.123"));
    assert(Pfloat(-0) > Pfloat(-0.01));
    assert(Pfloat(-1) > Pfloat(-1.1));
    assert(Pfloat(-1) > Pfloat(-1.01));
    assert(Pfloat(-.02) > Pfloat(-.03));
    assert(!(Pfloat(-.2) > Pfloat(-.03)));
    assert(Pfloat("-.2222222") > Pfloat(-.3));
    assert(!(Pfloat(-.12345) > Pfloat("-.123450")));
    assert(Pfloat(-.12345) > Pfloat(-.123451));
    assert(Pfloat(-1.23) < Pfloat(-1.22));
    assert(Pfloat(-0.9) >= Pfloat(-0.9));
    assert(Pfloat(-0.1) <= Pfloat("-50e-3"));
    assert(!(Pfloat("-0.5") > Pfloat(-0.5)));
    assert(!(Pfloat(-0.1) < Pfloat("-0.2")));
    assert(!(Pfloat("-2.0") >= Pfloat(-1.5)));
    assert(!(Pfloat(-0.3) <= Pfloat(-0.4)));
    assert(Pfloat("-0.00001") > Pfloat(-0.0001));
    assert(Pfloat(-100000) < Pfloat("1e6"));
    assert(Pfloat("-0.9999") >= Pfloat(-1.0));
    assert(Pfloat(-0.9999) <= Pfloat(-0.999));
    assert(!(Pfloat(-0.5) > Pfloat(-0.3)));
    assert(!(Pfloat(-0.1) < Pfloat(-0.1)));
    assert(!(Pfloat(-2.0) >= Pfloat(-1.5)));
    assert(!(Pfloat(-0.4) <= Pfloat(-0.5)));
    assert(Pfloat(-0) > (-1));
    assert(Pfloat(-0) > (-0.123));
    assert(Pfloat(-0) > (-0.01));
    assert(Pfloat(-1) > (-1.1));
    assert(Pfloat(-1) > (-1.01));
    assert(Pfloat(-.02) > (-.03));
    assert(!(Pfloat(-.2) > Pfloat("-.03")));
    assert(Pfloat("-.2222222") > Pfloat("-.3"));
    assert(!(Pfloat(-.12345) > (-.123450)));
    assert(Pfloat(-.12345) > (-.123451));
    assert(Pfloat(-1.23) < (-1.22));
    assert(Pfloat(-0.9) >= (-0.9));
    assert(Pfloat(-0.1) <= (-0.05));
    assert(!(Pfloat(-0.5) > (-0.5)));
    assert(!(Pfloat(-0.1) < (-0.2)));
    assert(!(Pfloat("-2.0") >= (-1.5)));
    assert(!(Pfloat(-0.3) <= (-0.4)));
    assert(Pfloat(-0.00001) > Pfloat("-0.0001"));
    assert(Pfloat(-100000) < (-10000));
    assert(Pfloat(-0.9999) >= (-1.0));
    assert(Pfloat(-0.9999) <= (-0.999));
    assert(!(Pfloat(-0.5) > (-0.3)));
    assert(!(Pfloat("-0.1") < (-0.1)));
    assert(!(Pfloat(-2.0) >= (-1.5)));
    assert(!(Pfloat(-0.4) <= (-0.5)));
    // === * tests
    assert(Pfloat(2) * Pfloat(3) == Pfloat(6));
    assert(Pfloat(1.5) * Pfloat(2.5) == Pfloat(3.75));
    assert(Pfloat(0) * Pfloat(5.5) == Pfloat(0));
    assert(Pfloat(-3.3) * Pfloat(0) == Pfloat(0));
    assert(Pfloat(1) * Pfloat(1) == Pfloat(1));
    assert(Pfloat(0.5) * Pfloat(0.5) == Pfloat(0.25));
    assert(Pfloat(1.23) * Pfloat(4.56) == Pfloat(5.6088));
    assert(Pfloat(2.5) * Pfloat(3) == Pfloat(7.5));
    assert(Pfloat(0.1) * Pfloat(0.2) == Pfloat(0.02));
    assert(Pfloat(2.0) * Pfloat(0.1) == Pfloat(0.2));
    assert(Pfloat(42.576) * Pfloat(192.3) == Pfloat(8187.3648));
    assert(Pfloat(8699) * Pfloat(15.68) == Pfloat("136400.32"));
    assert(Pfloat(.5)*Pfloat(.5)*Pfloat(".5")*Pfloat(.5)*Pfloat(.5)*Pfloat(".5") == Pfloat(".015625"));
    assert(Pfloat(2) * (3) == Pfloat(6));
    assert(Pfloat(1.5) * (2.5) == Pfloat(3.75));
    assert(Pfloat(0) * (5.5) == Pfloat(0));
    assert(Pfloat(-3.3) * (0) == Pfloat(0));
    assert(Pfloat(1) * (1) == Pfloat(1));
    assert(Pfloat(0.5) * (0.5) == Pfloat(0.25));
    assert(Pfloat(1.23) * (4.56) == Pfloat(5.6088));
    assert(Pfloat(2.5) * (3) == Pfloat(7.5));
    assert(Pfloat(0.1) * (0.2) == Pfloat(0.02));
    assert(Pfloat(2.0) * (0.1) == Pfloat(0.2));
    assert(Pfloat(42.576) * (192.3) == Pfloat(8187.3648));
    assert(Pfloat(8699) * (15.68) == Pfloat(136400.32));
    assert(Pfloat(.5)*.5*.5*.5*.5*.5 == Pfloat(.015625));
    // === multi-arithmetics tests
    assert(Pfloat("12345.67891") + Pfloat(54321.23456) == Pfloat(66666.91347));
    assert(Pfloat(156) - Pfloat(-.252) + Pfloat(85.2352) == Pfloat(241.4872));
    assert(Pfloat(-156) - Pfloat(-.252) + Pfloat("-85.2352") == Pfloat(-240.9832));
    assert(Pfloat() - Pfloat(0.0025) - Pfloat(4.23) == Pfloat(-4.2325));
    assert(Pfloat(.5)*Pfloat(.5)*Pfloat(.5) - Pfloat(".5") == Pfloat(.5)*(Pfloat(.5)*Pfloat(.5) - Pfloat("1")));
    assert(Pfloat(11.11)*Pfloat(22.22)*Pfloat(7) - Pfloat(11.11)*Pfloat(-7) == Pfloat(11.11)*Pfloat(7)*(Pfloat(22.22) + Pfloat(1)));
    assert(Pfloat(.654) + Pfloat(".2") - Pfloat(78) + Pfloat(-1200) - Pfloat(.56) == Pfloat(-1277.706));
    assert(Pfloat(-.2)*Pfloat(-4.2)*(Pfloat(1)-Pfloat(254.02)) - (Pfloat(78) + Pfloat(32.2)) == Pfloat("-322.7368")); // not rounded result = -111.2120008
    // === Pow tests
    assert(Pfloat(1).pow(5) == 1);
    assert(Pfloat(2).pow(5) == Pfloat(2)*2*2*2*2);
    assert(Pfloat(3).pow(5).pow(5) == Pfloat(3).pow(25));
    assert(Pfloat(-4).pow(8) == Pfloat(2).pow(16));
    assert(Pfloat(-4).pow(9) == Pfloat(2).pow(17)*(-2));
    assert(Pfloat(0).pow(0) == 1);
    assert(Pfloat(125425).pow(0) == 1);
    assert(Pfloat(.5).pow(50) == Pfloat("0.00000000000000088817841970012523233890533447265625"));
    std::cout << "all tests passed" << std::endl;
    */
    return 0;
}
