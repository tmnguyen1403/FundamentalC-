#include <iostream>

// fallthrough: tell compiler not issue warning for the fall through case since it is our intention, not logic error.
int main() {
    int grade_input{0};
    while (std::cin >> grade_input) {
        int grade = grade_input /10;
        switch (grade) {
            case 9:
                [[fallthrough]];
            case 10:
                std::cout << "A\n";
                break;
            case 8:
                std::cout << "B\n";
                break;
            case 7:
                std::cout << "C\n";
                break;
            case 6:
                std::cout << "D\n";
                break;
            case 5:
                std::cout << "E\n";
                break;
            default:
                std::cout << "F\n";
                break;
        }
    }
    return 0;
}