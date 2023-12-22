#include <vector>
#include <iostream>

class Solution {
public:
    std::vector<int> majorityElement(std::vector<int>& nums) {
        std::vector<int> result{};
        if (nums.size() == 1) {
            result.push_back(nums[0]);
            return result;
        }
        //Voting mechanism
        //Initial c1 and c2 with two different values
        int c1 = 0;
        int count1 = 0;
        int c2 = 1;
        int count2 = 0;
        for (const auto& num : nums) {
            if (c1 == num)
                ++count1;
            else if (c2 == num)
                ++count2;
            else if (count1 == 0){
                c1 = num;
                count1 = 1; 
            }
            else if (count2 == 0) {
                c2 = num;
                count2 = 1;
            }
            else {
                count1 -= 1;
                count2 -= 1;
            }
        }

        //Check for majority
        count1 = 0;
        count2 = 0;
        for (const auto& num : nums) {
            if (c1 == num)
                ++count1;
            else if (c2 == num)
                ++count2;
        }
        if (count1 > nums.size() / 3)
            result.push_back(c1);
        if (count2 > nums.size() / 3)
            result.push_back(c2);

        return result;
    }
};

int main()
{
    Solution s;
    std::vector<int> nums;
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(3);

    auto result = s.majorityElement(nums);
    std::cout << "Hello result\n";
    for (const auto& num: result) {
        std::cout << num << " \n"; 
    }
}