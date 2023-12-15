#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> result(nums.size());
        int left = 0, right = nums.size() - 1;

        for (auto index = right; index >=0;--index) {
            auto num = abs(nums[left]);
            if (num > abs(nums[right])) {
                left += 1;
            } else {
                num = nums[right];
                right -= 1;
            }
            result[index] = num*num;
        }
        return result;
    }
};

int main() {

    Solution so;

    vector<int> nums;
    nums.push_back(-1);
   // nums.push_back(2);

    auto result = so.sortedSquares(nums);
    std::cout << "result\n";
    for(auto n : result) {
        std::cout << n << " " << std::endl;
    }
    return 0;
}