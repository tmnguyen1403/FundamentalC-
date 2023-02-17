#include <iostream>
#include <random>
#include <ctime>

//this random library provides a more secure 
int main() {
    //initialize the engine with seed value as current time
    std::default_random_engine engine{static_cast<unsigned int>(time(0))};
    std::uniform_int_distribution<int> randomInt{1,6};

    for (int counter{1}; counter <= 10; ++counter) {
        std::cout << randomInt(engine) << " ";
    }
    std::cout << std::endl;
    return 0;
}