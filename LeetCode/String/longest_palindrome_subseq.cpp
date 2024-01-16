class Solution {
public:
    int longestPalindromeSubseq(string s) {
        size_t n = s.length();
        std::vector<std::vector<int>> dp{n, std::vector<int>(n,0)};
        for (auto i = 0; i < n; ++i)
            dp[i][i] = 1; //max of s[i:i] = 1 - length 1
        for (auto currentLength = 2; currentLength <= n; ++currentLength) {
            for (auto i = 0; i < n - currentLength+1;++i) {
                auto j = i + currentLength - 1;
                if (s[i] == s[j]) {
                    if (currentLength == 2)
                        dp[i][j] = 2;
                    else
                        dp[i][j] = dp[i+1][j-1] + 2;
                } else
                    dp[i][j] = std::max(dp[i][j-1],dp[i+1][j]);
            }
        }
        return dp[0][n-1];
    }
};