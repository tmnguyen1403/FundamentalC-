#include <iostream>

int main(){
    int number{10};

    std::cout << "This is the C++20 feature used for compiler optimization!\n";
    if (number != 10) [[likely]] {
        std::cout << "Likely is used to tell compiler for optimization\n";
    } else [[unlikely]] {
        std::cout << "Unlikely is used in vice verser.\n";
    }
    return 0;
}