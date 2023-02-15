#include <iostream>
#include <string>

int main() {
    std::cout << "Hello world!\n";
    std::string s1{"hello"};
    std::string s2{"world"};

    //std::boolalpha - sticky iomanipulator, will display true false instead of 1 0
    std::cout << "s1 == s2? " << std::boolalpha << (s1 == s2) << std::endl;
    std::cout << "s1 != s2? " << (s1 != s2) << std::endl;

    //Testing new C++20
    std::cout << "\ns1 starts with he: " << s1.starts_with("he") << std::endl;
    std::cout << "\ns1 ends with lo: " << s1.ends_with("lo") << std::endl;
    return 0;
}