#include <iostream>
#include <iomanip>
#include <cstdlib>

int main() {
    int seed{12345};
    char c;

    while (std::cin >> c) {
        std::cout << "Roll a dice (1-6):\n";
        std::cout << 1 + rand() % 6 << std::endl;
    }
    return 0;
}