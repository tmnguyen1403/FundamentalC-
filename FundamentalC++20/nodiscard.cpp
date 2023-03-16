#include <iostream>

/*
[[nodiscard]] cause compilers to issue warning if you ignore the return value of the function
*/
[[nodiscard ("reasoning for this")]]
bool empty() {
    return true;
}

int main() {
    empty();  //clang warning: ignoring return value of function declared with 'nodiscard' attribute [-Wunused-result]
    if (empty()) {
        std::cout << "this is emtpy\n";
    }
    return 0;
}