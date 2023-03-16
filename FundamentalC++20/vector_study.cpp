#include <vector>
#include <iostream>
#include <ranges>
#include <iomanip>
#include <stdexcept>

void printVector(const auto& v, std::string message) {
    std::cout << message << std::endl;
    for (const auto& value: v) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers1, numbers2;
    auto numbers = std::views::iota(1,11);
    for (auto number: numbers) {
        numbers1.push_back(number*number);
        numbers2.push_back(number*number*number);
    }
    printVector(numbers1, "vector1");
    printVector(numbers2, "vector2");
    std::cout << "Vector compare:\n" << std::boolalpha;
    //this will compare size first, then if size is equal, comparing element by element
    std::cout << "numbers1 != numbers2: " << (numbers1 != numbers2) << std::endl;

    //Copy operator
    std::vector<int> numbers3{numbers1};
    printVector(numbers3, "vector3 values are copied from vector1");
    std::cout << "numbers1 != numbers3: " << (numbers1 != numbers3) << std::endl;
    
    //assigment operator
    numbers3 = numbers2;
    printVector(numbers3, "vector3 values are assigned with vector2 values");
    std::cout << "numbers2 == numbers3: " << (numbers2 == numbers3) << std::endl;

    //handle exception when accessing value in vector
    try
    {
        numbers3.at(12);
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}