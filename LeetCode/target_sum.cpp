#include <map>
#include <iostream>
#include <tuple>
#include <vector>
#include <array>

class Solution {
public:
    using index_sum_pair = std::tuple<size_t, int>;
// 2d array? This is not a good store ds since the sum can be any number
// map
// unorderred_map : Need to create a hash function for tuple
//Using recursive to find all possible combination
//Using map to store visited solution

    //Bottom up
    template<typename NumArray>
    int helper(const NumArray& nums, const size_t& index, const int& current_sum,const int& target) {
        if (ways.find({index,current_sum}) != ways.end())
            return ways[{index,current_sum}];
        if (index == nums.size())
            return current_sum == target ? 1 : 0;
        auto total_ways = helper(nums, index + 1, current_sum + nums[index], target) + helper(nums, index+1, current_sum - nums[index], target);     
        ways[{index,current_sum}] = total_ways;
        return total_ways;
    }
    template<typename NumArray>
    int findTargetSumWays(NumArray& nums, int target) {
        helper(nums, 0, 0, target);
        return ways[{0,0}];
    }

    //Top Down
    template<typename NumArray>
    int helper_topdown(const NumArray& nums, const size_t& index, const int& current_sum,const int& target) {
        if (ways.find({index,current_sum}) != ways.end()) {
            return ways[{index,current_sum}];
        }
        if (index == 0)
            return current_sum == 0 ? 1 : 0;
        auto total_ways = helper_topdown(nums, index - 1, current_sum + nums[index-1], target) + helper_topdown(nums, index-1, current_sum - nums[index-1], target);     
        ways[{index,current_sum}] = total_ways;
        return total_ways;
    }
    template<typename NumArray>
    int findTargetSumWays_topdown(NumArray& nums, int target) {
        helper_topdown(nums, nums.size(), -target, target);
        return ways[{nums.size(),-target}];
    }

    void reset() {
        ways.clear();
    }
    void debug() {
        std::cout << "ways\n";
        for (auto& [pair, value]: ways) {
            std::cout << value << "\n";
        }
    }
private:
    std::map<index_sum_pair, uint64_t> ways;
};

int main() {
    Solution s;
    std::array<int, 5> nums = {1,1,1,1,1};
    auto target = 3;
    auto result = s.findTargetSumWays(nums, target);
    std::cout << "Result: " << result << std::endl;
    s.reset();
    {
        std::vector<int> nums;
        nums.resize(5);
        std::fill_n(nums.begin(), 5, 1);

        auto result = s.findTargetSumWays(nums, target);
        std::cout << "Result: " << result << std::endl;
        //s.debug();
        s.reset();
    }

    {
        std::vector<int> nums;
        auto length = 5;
        nums.resize(length);
        std::fill_n(nums.begin(), length, 1);
        auto target = 3;
        auto result = s.findTargetSumWays_topdown(nums, target);
        std::cout << "Result: " << result << std::endl;
        //s.debug();
        s.reset();
    }

}