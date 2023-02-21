#include <iostream>
#include <regex>
#include <iomanip>
/*
Character classes
+ \d - any digit (0-9)
+ \D - not digit
+ \s - any whitespace character (spaces, tabs, and newlines)
+ \S - not whitespace
+ \w - word character - alphanumeric character, underscore
+ \W - not word character
*/
int main() {
    std::regex r1("02345");
    std::cout << "Matching against: 02345\n" << std::boolalpha
        << "02345: " << std::regex_match("02345", r1) << std::endl
        << "23450: " << std::regex_match("23450", r1)
        << std::endl;

    std::cout <<"Matching five digits:\n";
    std::regex r2(R"(\d{5})"); //using Raw string litral because of backslash(\) character
    std::cout << "12334" << std::regex_match("12334", r2) << std::endl;
    std::cout << "123" << std::regex_match("123", r2) << std::endl;
    std::cout << "789987" << std::regex_match("789987", r2) << std::endl;

    std::cout << "Match a word that starts with a capital letter\n";
    std::regex r3("[A-Z][a-z]*");
    std::cout << "Mike: " << std::regex_match("Mike", r3) << std::endl;
    std::cout << "lucas: " << std::regex_match("lucas", r3) << std::endl;

    std::cout << "Match any character that's not a lowercase letter\n";
    std::regex r4("[^a-z]");
    std::cout << "A:" << std::regex_match("A", r4) << std::endl;
    std::cout << "b:" << std::regex_match("b", r4) << std::endl;
    std::cout << "AB:" << std::regex_match("AB", r4) << std::endl;

    std::cout << "Match [A-Z][a-z]+ - a capital letter followed by at least one loweraase letter:\n";
    std::regex r5("[A-Z][a-z]+");
    std::cout << "Visage: " << std::regex_match("Visage", r5) << std::endl;
    std::cout << "wizard: " << std::regex_match("wizard", r5) << std::endl;
    std::cout << "Visage Kilimore " << std::regex_match("Visage Kilimore", r5) << std::endl;

    std::cout << "labell?ed - matching zero or one occurence of a subexpression\n";
    std::regex r6("labell?ed");
    std::cout << "labelled: " << std::regex_match("labelled", r6) << std::endl;
    std::cout << "labeled: " << std::regex_match("labeled", r6) << std::endl;
    std::cout << "labellled: " << std::regex_match("labellled", r6) << std::endl;

    std::cout << "matching n or more occurences (\\d{3,}):\n";
    std::regex r7(R"(\d{3,})");
    std::cout << "123" << std::regex_match("123", r7) << std::endl;
    std::cout << "12345" << std::regex_match("12345", r7) << std::endl;
    std::cout << "123321" << std::regex_match("123321", r7) << std::endl;

    std::cout << "matching [m,n] occurences (\\d{3,5}):\n";
    std::regex r8(R"(\d{3,5})");
    std::cout << "123" << std::regex_match("123", r8) << std::endl;
    std::cout << "12345" << std::regex_match("12345", r8) << std::endl;
    std::cout << "123321" << std::regex_match("123321", r8) << std::endl;

    std::cout << "replacing substring std::regex_replace:\n";
    std::string s1("1\t2\t3\t4");
    std::cout << R"(original string: 1\t2\t3\t4)" << std::endl;
    std::cout << "Replacing tab with comma: " << std::regex_replace(s1, std::regex{R"(\t)"}, ",") <<std::endl;

    std::cout << "searching for matches:\n";
    std::string s2{"Hello world, do you remember me?"};
    std::cout << "world: " << std::regex_search(s2,std::regex("world")) << std::endl;
    std::cout << "r: " << std::regex_search(s2,std::regex("r")) << std::endl;
    std::cout << "you:" << std::regex_search(s2,std::regex("you")) << std::endl;

    std::cout << "search with case  insensitive\n";
    std::string s3{"HARRY PORTER"};
    std::smatch match; //store the text that matches the pattern
    std::cout << "Harry: " << std::regex_search(s3, match, std::regex("Harry", std::regex_constants::icase)) << std::endl;
    std::cout << "Matched text: " << match.str() << std::endl;

    std::cout << "find all matches: \n";
    std::string s4{"Phone numbers: 123-456-7777 345-234-7412\n"};
    std::regex phone(R"(\d{3}-\d{3}-\d{4})");

    std::cout << "Finding all phone number in: " << s4 << std::endl;
    while (std::regex_search(s4, match, phone)) {
        std::cout << "matched number: " << match.str() << std::endl;
        s4 = match.suffix(); // the rest of the original context after the matched number
    }
    return 0;
}