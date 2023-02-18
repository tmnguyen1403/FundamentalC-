#include <array>
#include <iostream>
#include <numeric>
#include <vector>
#include <span>

int main() {
    //span is recommended to passed by value since it is a pointer
    auto displaySpan = [](std::span<const int> items) {
        for (auto& item: items) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    };

    auto square = [](std::span<int> items) {
        for (auto & item: items) {
            item = item*item;
        }
    };
    int values1[5]{1,2,5,6,7};
    displaySpan(values1);
    square(values1);
    displaySpan(values1);

    //accumulate
    std::span<int> acspan{values1};
    std::cout << "total" << std::accumulate(std::begin(acspan), std::end(acspan), 0);
    std::cout << std::endl;

    //create subview
    std::cout << "first 3 elements: ";
    displaySpan(acspan.first(3));
    std::cout << "last 3 elements: ";
    displaySpan(acspan.last(3));
    std::cout << "elements 1..3: ";
    displaySpan(acspan.subspan(1,3));

    return 0;
}   