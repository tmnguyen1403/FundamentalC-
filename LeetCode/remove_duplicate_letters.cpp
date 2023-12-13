/*
https://leetcode.com/problems/remove-duplicate-letters/
*/
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <numeric>
#include <stack>
#include <string_view>

//Only for code practice
using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) const {
        //preprocess string to store the last occurence of each character in string
        //This allows us to check whether the character can be removed from the current stack since it will reappear later
        std::array<size_t, 26> last_occurrences;
        for (auto index = 0; index < s.length(); ++index) {
            char c = s[index];
            last_occurrences[c- 'a'] = index;
        }

        //Fast look up 
        std::array<bool, 26> in_stack{};
        fill_n(in_stack.begin(), in_stack.size(), false);
        //using stack to solve the problem
        stack<char> char_stack{};
        /*
        * Time complexity: O(n)
        */
        for (auto index = 0; index < s.length(); ++index) {
            char c = s[index];
            if (!in_stack[c-'a']) {
                /*
                * Time complexity: constant
                * Worst case scenario is when it has to pop all alphabet character in the stack,
                * which is only 25 characters (cannot pop 'a'), and it occurs at every 26th time.
                * Therefore, the while loop is constant
                * Example worst case: "a..za..za..za..z"
                */
                while (!char_stack.empty()) {
                    const char& top_c = char_stack.top();
                    if (c < top_c && index < last_occurrences[top_c - 'a']) {

                        char_stack.pop();
                        in_stack[top_c-'a'] = false;
                    }
                    else
                        break;
                }
                char_stack.push(c);
                in_stack[c-'a'] = true;
            }
        }

        //Build the result string
        std::string result{};
        result.resize(char_stack.size());
        {
            auto index = result.length() - 1;
            while (!char_stack.empty()) {
                const auto& top_c = char_stack.top();
                result[index] = top_c;
                char_stack.pop();
                --index;
            }
        }

        return result;
    }
    std::string operator()(const std::string& s) const {
        return removeDuplicateLetters(s);
    }
};

template <typename InputT, typename OutputT, typename FunctionT>
void test(InputT input, OutputT expect, const FunctionT& f, std::string_view message) {
    std::cout << message << " \n"; 
    auto result = f(input);
    std::cout << "result: " << result << "\n";
    std::cout << "expect: " << expect << "\n";
    assert(result == expect && "Result is different thant expected");
}

int main()
{
    Solution so;

    //Test case 1
    {
        auto s = "bcabc";
        auto expect = "abc";
        test(s,expect, so, "Test 1");
    }
    //Test case 2
    {
        auto s = "cbacdcbc";
        auto expect = "acdb";
        test(s,expect, so, "Test 2");
    }
    return 0;
}