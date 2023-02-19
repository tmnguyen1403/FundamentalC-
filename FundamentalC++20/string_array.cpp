#include <iostream>
#include <array>

int main() {
    const auto display = [](const auto& items) {
        for (const auto& item: items) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    };

    //create a one-element array<const char*>
    const auto array1 = std::array{"hello"};
    std::cout << array1.size() << std::endl;
    display(array1);
    //create a std::array<char>
    const auto array2 = std::to_array("hello");
    std::cout << array2.size() << std::endl;
    display(array2);
    return 0;
}