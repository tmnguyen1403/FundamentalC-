#include <iostream>

/*
Overloading function means valid functions in the same scope must have different signatures
Signature:
+ name + parameter list
*/

void hello(int number) {
    std::cout << "Hello int: " << number << std::endl;
}
void hello(double number) {
    std::cout << "Hello double: " << number << std::endl;
}
void hello(float number) {
    std::cout << "Hello float: " << number << std::endl;
}
int main() {
    hello(10);
    hello(10.0);
    hello(10.0f);
    return 0;
}