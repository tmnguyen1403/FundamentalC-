/*
Virtual
+ with virtual functions, the type of the object pointed to (or referenced) - no the type of the pointer handle -
determines which member function to invoke
+ once a function is declared virtual, it's virtual in all classes derived directly or indirectly from that base class
+ there is overhead cost of using virtual function to look up the right pointer

+ DO NOT call VIRTUAL functions from constructors and destructors.
The reason is that non-polymorphic behavior occurs in the context of Constructors and destructor in C++.
If a virtual function is called in base class constructor, it calls the base class version.

+ include a virtual destrutor in every class that contains virtual functions

*/

#include <iostream>
#include <string>

class Shape { // abstract class, italicized in UML
    public:
        //pure vitrual functions, cannot create an object of base class, yet pointers and refereces can be created
        //derived class must provide the implementation of the pure virtual function, otherwise derived classes became abstract classes too
        virtual void draw() const = 0; 
        virtual ~Shape() = default;
};

//Final keyword is used to indicate that the Triangle class cannot be derived further
class Triangle final : public Shape 
{
    public:
        void draw() const override {
            std::cout << "Draw triangle\n";
        }
};

class Base
{
    public:
        virtual std::string hello() const {
            return "Hello base";
        }
    virtual ~Base() = default; // auto-generate the virual destructor, derived class destructors are also virtual as well
};

class Derived : public Base 
{
    public:
        std::string hello() const override {
            return "Hello derived";
        }
};

int main() {
    Base base;
    Derived derived;
    std::cout << "normal object\n";
    std::cout << base.hello() << std::endl;
    std::cout << derived.hello() << std::endl;
    
    Base* bptr{&base};
    std::cout << "using base pointers\n";
    std::cout << bptr->hello() << std::endl;
    std::cout << "aimed based pointer at derived class object\n";
    bptr = &derived;
    std::cout << bptr->hello() << std::endl;
    std::cout << "using derived pointers\n";
    Derived* dptr{&derived};
    std::cout << dptr->hello() << std::endl;
    std::cout << "aimed derived pointer at the base class object\n";
    //dptr = &base;
    std::cout << "It is not allowed because derived class is not a base class\n";
    
    std::cout << "Abstract base class\n";
    Triangle triangle{};
    Shape * pshape{&triangle};
    pshape->draw();
    return 0;
}