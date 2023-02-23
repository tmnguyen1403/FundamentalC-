/*
+ perfer single/inheritance and/or composition
+ inherit members of two or more base classes
+ Common problem:
_ data members or member functions with the same name
_ can lead to ambiguity
+ ISO C++ FAQ recommends multiple inheritance from only interfaces
*/
#include <string>
#include <iostream>

class Base1 {
    public:
        explicit Base1(int number): m_number{number}{};
        int getData(){return m_number;};
    private:
        int m_number;
};

class Base2 {
    public:
        explicit Base2(char c): m_char{c}{};
        char getData(){return m_char;};
    private:
        char m_char;
};

class Derived : public Base1, public Base2 {
    public:
        Derived(int value, char letter, double real): Base1{value}, Base2{letter}, m_real{real} {};
        double getReal() {return m_real;};
        std::string toString() {
            return  std::to_string(Base1::getData()) + 
                std::to_string(Base2::getData()) + std::to_string(getReal());
        }
    private:
        double m_real;
};

int main() {
    Derived derived{10, 'F', 20.0};
    std::cout << derived.toString() << std::endl;
    std::cout << "derived base1 getData: " << derived.Base1::getData() << std::endl;
    std::cout << "derived base2 getData: " << derived.Base2::getData() << std::endl;

    std::cout << "derived can be treated as base1 or base2\n";
    Base1* pt1{&derived};
    std::cout << "base1 ptr data: " << pt1->getData() << std::endl;
    Base2* pt2{&derived};
    std::cout << "base2 ptr data: " << pt2->getData() << std::endl;
    return 0;
}