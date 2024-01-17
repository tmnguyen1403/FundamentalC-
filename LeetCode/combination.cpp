class Solution {
    std::vector<std::vector<int>> result;
    int n_;
    int k_;
public:
    void helper(std::vector<int>& com, int com_index, int left)
    {
        auto right = n_ - k_ + 1 + com_index;
        for (;left <= right;++left)
        {
            com[com_index] = left;
            if (com_index + 1 == k_){
                result.push_back(com);
            } else
            {
                helper(com,com_index + 1,left+1);
            }
        }

    }
    vector<vector<int>> combine(int n, int k) {
        n_ = n;
        k_ = k;
        std::vector<int> com(k,0);
        helper(com, 0, 1);
        return result;
    }
};