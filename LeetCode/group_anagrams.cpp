#include <unordered_map>

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        //map the hash value to the index in the result vector
        std::unordered_map<std::string, int> store_result;
        std::vector<std::vector<std::string>> result;
        for (const auto& s: strs) {
            auto sorted_str = s;
            std::sort(sorted_str.begin(), sorted_str.end());
            if (store_result.find(sorted_str) == store_result.end()) {
                std::vector<std::string> tmp{s};
                result.push_back(tmp);
                store_result[sorted_str] = result.size() - 1;
            } else {
                result[store_result[sorted_str]].push_back(s);
            }
        }
        return result;
    }
};