#include <iostream>
#include <array>
#include <numeric>

int main() {
    constexpr size_t array_size{5};
    std::array<int, array_size> numbers{200,42,314,523,412};
    std::cout << "sum of all numbers: " << std::accumulate(std::begin(numbers), std::end(numbers), 0);
    std::cout << std::endl;
    return 0;
}