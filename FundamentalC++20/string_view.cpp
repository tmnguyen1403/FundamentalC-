#include <string_view>
/*
Read-only views of C-string or std::string objects
Contains:
+ a pointer to the first character in a contiguos sequence
+ a count of the number of characters
+ std::string-style operations on C-string without creating std::string
- use std::string if need to modify the content of the string 
*/
#include <iostream>
#include <string>

int main() {
    std::string s1{"hello world!"};
    std::string s2{s1};
    std::string_view v1{s1};

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "v1: " << v1 << std::endl;

    std::cout << "modify s1 manifest into v1:\n";
    s1.at(2) = 'k';
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "v1: " << v1 << std::endl;

    std::cout << "remove prefix or suffix\n";
    v1.remove_prefix(1); // remove 1 character from the front
    v1.remove_suffix(2); //remove 2 characters from the back
    std::cout << "v1: " << v1 << std::endl;

    //iterable
    for (auto& c: v1) {

        std::cout << c << " ";
    }
    std::cout << std::endl;
    return 0;
}