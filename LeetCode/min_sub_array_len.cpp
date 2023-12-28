#include <vector>
class Solution {
public:
    int minSubArrayLen(int target, std::vector<int>& nums) {
       int total = 0;
       int left = 0;
       int right = 0;
        int min_length = nums.size()+1;
        while (right < nums.size()) {
            total += nums[right];
            ++right;
            while (total >= target) {
                min_length = min_length < right - left ? min_length : right - left;
                total -= nums[left];
                ++left;
            }
        } 
       return min_length == nums.size() + 1 ? 0 : min_length;
    }
};