#include <string>
#include <iostream>

int main() {
    std::string s("100.123hello");
    std::cout << s << std::endl;
    std::cout << "stoi(s): " << stoi(s) << std::endl;
    std::size_t not_converted_index{0};
    std::size_t *ptr_index{&not_converted_index};
    std::cout << "stoi(s,ptr,base10): " << stoi(s,ptr_index,10) << std::endl;
    std::cout << "index of first non-converted char: " << *ptr_index << std::endl;
    
    std::cout << "\nconvert to double\n";
    std::cout << "stod(s): " << stod(s) << std::endl;

    return 0;
}