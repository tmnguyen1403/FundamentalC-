#include <ranges>
#include <iostream>
#include <numeric>
#include <array>
#include <map>
/*
_ A range is a collection of elements that you can iterate over
_ A view enables you to specify an operation that manipulates a range
 + views are composable - you can chain them together to process 
 a range's lements through multiple operations
*/
/*
Need to use gcc image on docker hub to compile since 
clang standard library does not implement this.
*/

int main() {
    // using my_views = std::ranges::views;

    auto showValues = [](auto &values, const std::string& message) {
        std::cout << message << ": ";
        for (auto value: values) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    };

    //lazy generation, reduce memory consumption due to generate value on demand

    auto values1 = std::views::iota(1,11); //declare that we want to generate range 1..10, not actually generate it
    showValues(values1, "Generate integers 1-10");

    auto values2 =
        values1 | std::views::filter([](const auto& x){return x % 2 ==0;});
    showValues(values2, "Get even number ");

    auto values3 = 
        values2 | std::views::transform([](const auto& x){return x*x;});
    showValues(values3, "Square of even nummber");
    auto values4 = 
        values1 | std::views::filter([](const auto& x){return x % 2 != 0;})
            | std::views::transform([](const auto& x){return x*x*x;});
    
    showValues(values4, "Cubic of odd nummber");

    //apply to a container
    std::array<int, 10> numbers{1,2,3,4,5,6,7,8,9,10};
    auto values5 = numbers 
        | std::views::filter([](const auto &x) {return x % 2 == 0;});
    showValues(values5, "even number of array numbers");

  std::map<char, int> map{ {'A', 1}, {'B', 2}, {'C', 3}, {'D', 4}, {'E', 5} };
    auto odd = [](int x) { return 0 != (x & 1); };

    std::cout << "\nCheck address to verify if views create copy or not.";
    std::cout << "\nOriginal. No views\n";
    for (auto & val: map) {
        std::cout << &val.second << " ";
    }
    std::cout << std::endl;
    //references
    //https://en.cppreference.com/w/cpp/ranges/values_view
    auto v6 = map | std::views::values | std::views::filter(odd);
    std::cout << "\nView odd values address\n";
    for (auto &t: v6) {
        std::cout << &t << " ";
    }

    std::cout << "\nodd values in the map: ";
    for (int value : map | std::views::values | std::views::filter(odd)) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::cout << "\nView keys in the map\n";
    auto keys = map | std::views::keys;
    for (auto &key: keys){
        std::cout << key << " ";
    }
    std::cout << "\n";
    return 0;
}