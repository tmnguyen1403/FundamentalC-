#include <iostream>

class Base{
    public:
        virtual void print() const = 0;
};

class Derived1 : virtual public Base{
    public:
        void print() const { std::cout << "derived1\n";}
};

class Derived2 : virtual public Base{
    public:
        void print() const { std::cout << "derived2\n";}
};

/*
Virtual inheritance affect the Multiple class.
It only brings one copy of the Base class; eliminating the two separate Base object problem
*/
class Multiple : public Derived1, public Derived2{
    public:
        void print() const { std::cout << "multiple"; Derived2::print();}
};

int main()
{
    Multiple multiple{};
    Derived1 derived1{};
    Derived2 derived2{};
    Base* bases[3];
    //bases[0] = &multiple; - error due to two object of bases are created - one from derived1 and one from derived2
    //fix by using virtual inheritance
    bases[0] = &multiple;
    bases[1] = &derived1;
    bases[2] = &derived2;
    
    bases[0]->print();
    bases[1]->print();
    bases[2]->print();
    return 0;
}

