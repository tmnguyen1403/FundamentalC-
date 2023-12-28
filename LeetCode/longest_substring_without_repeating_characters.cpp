#include <unordered_map>
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        if (n <= 1)
            return n;
        std::unordered_map<char, int> seen_chars;
        int left = 0;
        int right = 0;
        int max_length = 1;
        while (right < n) {
            char c = s[right];
            if (seen_chars.find(c) == seen_chars.end())
                seen_chars[c] = 0;
            seen_chars[c] += 1;
            //if found duplicate, moving left
            while (seen_chars[c] > 1) {
                seen_chars[s[left]] -= 1;
                ++left;
            }
            ++right;
            auto tmp_length = right - left;
            if (tmp_length > max_length)
                max_length = tmp_length;
        }
        return max_length;
    }
};