class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 1)
            return strs[0];
        size_t length = 0;
        bool is_prefix = true;
        for (size_t index = 0; index < strs[0].length();++index) {
            for (const auto& s : strs) {
                if (s[index] != strs[0][index]) {
                    is_prefix = false;
                    break;
                }
            }
            if (!is_prefix) {
                break;
            }
            ++length;
        }
        return strs[0].substr(0,length);
    }
};