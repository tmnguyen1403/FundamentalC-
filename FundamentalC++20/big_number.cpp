#include <iostream>
// #include <format>

int main(){
    long long value1{9'123'423'232'232'324'322ll};
    std::cout << "value1: " << value1 << std::endl;
    //not implemented in libc++
    // std::cout << std::format("test fmt std format: {}\n", 10);
    return 0;
}