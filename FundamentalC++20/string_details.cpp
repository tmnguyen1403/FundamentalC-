#include <iostream>
#include <string>

int main() {
    /*
    Default capacity varies depending on the compiler
    */
    const auto printStats = [](const std::string &s) {
        std::cout << "capacity: " << s.capacity()
            << " max size: " << s.max_size()
            << " size: " << s.size()
            << " empty: " << s.empty()
            << std::endl;
    };
    std::string string1;
    std::cout << "before input:\n ";
    printStats(string1);

    std::cout << "enter string: ";
    std::cin >> string1;
    printStats(string1);

    std::cout << "enter string: ";
    std::cin >> string1;
    printStats(string1);

    //Finding substring
    std::string s{"Hello world! Are you ready to rock and roll?"};
    std::cout << "string s: " << s << std::endl;
    std::cout << "\ns.find(rock): "<< s.find("rock")<< std::endl;
    std::cout << "\ns.rfind(rock): "<< s.rfind("rock")<< std::endl;

    //Find the very first of any character in the string rock 
    std::cout << "\ns.find_first_of(rock)" << s.find_first_of("rock") << std::endl;
    std::cout << "\ns.find_first_not_of(rock)" << s.find_first_not_of("rock") << std::endl;

    //erasing
    s = "Why are you talking to me??!!";
    std::cout << "s: " << s << std::endl;
    s.erase(10); // erase from index 10 through end of string s
    std::cout << "s.erase(10): " << s << std::endl;

    //replacing
    std::size_t position = s.find(" ");
    //replace all spaces with dash
    while (position != std::string::npos) {
        s.replace(position, 1, "-");
        position = s.find(" ", position + 1); // find space after index position + 1
    };
    std::cout << "s after replace: " << s << std::endl;
    
    //insert
    s.insert(s.find_last_of("-"), "darkmagician-");
    std::cout << "s after insert: " << s <<std::endl;
    
    return 0;
}