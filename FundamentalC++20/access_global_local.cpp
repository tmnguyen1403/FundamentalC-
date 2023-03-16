#include <iostream>
// using unary scope resolution operator to access global variable

const int prime{3};

int main() {
    const double prime{5.0};

    std::cout << "local prime: " << prime << std::endl;
    std::cout << "global prime: " << ::prime << std::endl;
    return 0;
}