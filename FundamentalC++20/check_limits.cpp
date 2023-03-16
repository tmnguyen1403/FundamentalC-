#include <limits>
#include <iostream>

int main() {
    std::cout << "long min: " << std::numeric_limits<long long>::min() << std::endl;
    std::cout << "long max: " << std::numeric_limits<long long>::max() << std::endl;
    return 0;
}