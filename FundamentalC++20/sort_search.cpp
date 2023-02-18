#include <iostream>
#include <array>
#include <algorithm>
#include <string>
#include <iomanip>
int main() {
    constexpr size_t array_size{7};
    std::array<std::string, array_size> colors {
        "red", "orange", "yellow",
        "green", "blue", "indigo", "violet"
    };
    std::cout << "before sort\n";
    for (const auto& color : colors) {
        std::cout << color << " "; 
    }
    std::cout << std::endl;
    std::sort(std::begin(colors), std::end(colors));
    std::cout << "after sort\n";
    for (const auto& color : colors) {
        std::cout << color << " "; 
    }
    std::cout << std::endl;
    std::cout << "binary search: has violet? " << std::boolalpha;
    std::cout << std::binary_search(std::begin(colors),std::end(colors) ,"violet") << std::endl;
    return 0;
}
