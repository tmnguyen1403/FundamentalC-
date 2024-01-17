class Solution {
std::vector<string> result;
public:
    void helper(std::string& s, int s_index, int n_open, int n_close, int n)
    {
        if (n_open == n_close && n_open == n) {
            result.push_back(s);
            return;
        }
        
        if (n_open < n) {
            s[s_index] = '(';
            helper(s,s_index + 1,n_open+1,n_close,n);
        }
        if (n_open > n_close) {
            s[s_index] = ')';
            helper(s,s_index + 1,n_open,n_close+1,n);
        }
    }
    
    vector<string> generateParenthesis(int n) {
        std::string s(n*2, '\0');
        helper(s,0,0,0,n);
        return result;
    }
};