#include <unordered_map>
class Solution {
    std::array<int, 26> char_primes;
public:
    Solution() {    
        char_primes[0] = 2;
        auto index = 1;
        auto number = 3;
        while (index < 26) {
            //Find the next prime number
            bool not_prime = true;
            while (not_prime) {
                bool found_prime = true;
                for (auto i =0;i<index;++i) {
                    if (number % char_primes[i] == 0)
                    {
                        found_prime = false;
                        break;
                    }
                }
                if (found_prime)
                {
                    not_prime = false;
                    break;
                }
                number += 2;
            }
            char_primes[index] = number;
            ++index;
        }
    }
    auto frequencyTable(std::string_view s) {
        std::unordered_map<char, uint32_t> counters;
        for (auto c: s) {
            if (counters.find(c) == counters.end())
                counters[c] = 0;
            counters[c] += 1;
        }
        return counters;
    }

    auto RabinFinger(std::string_view s, int base, int prime) {
        auto hash_value = 0;
        for (auto c: s) {
            hash_value = (base * hash_value + (c - 'a' + 1)) %prime;
        }
        return hash_value;
    }

    bool isAnagram(string s, string t) {
        //first approach: frequency count
        /*auto counter_s = frequencyTable(s);
        auto counter_t = frequencyTable(t);
        if (counter_s.size() != counter_t.size())
            return false;
        for (auto [key,value]: counter_s) {
            auto f_t = counter_t.find(key) == counter_t.end() ? 0 : counter_t[key];
            if (f_t != value)
                return false;
        }
        return true;
        */
        //second approach: string sort?
        /*std::sort(s.begin(),s.end());
        std::sort(t.begin(),t.end());
        return s == t;*/
        //third approach: use prime number?
        /**/

        auto sum_s = 0;
        auto sum_t = 0;
        for (auto c:s) {
            sum_s += (char_primes[c - 'a'] * (c-'a'+1)) % 101;
        }
        for (auto c:t) {
            sum_t += (char_primes[c - 'a'] * (c-'a'+1)) % 101;
        }
        return sum_s == sum_t;
        
    }
};