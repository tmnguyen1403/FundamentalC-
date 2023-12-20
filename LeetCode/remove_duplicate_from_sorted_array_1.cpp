class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int remove_index = 0, dup_count = 1;
        for (int index = 1; index < nums.size(); ++index) {
            if (nums[index-1] == nums[index])
                ++dup_count;
            else
                dup_count = 1;
            if (dup_count > 1) {
                if (remove_index == 0)
                    remove_index = index;
                continue;
            }
            if (remove_index > 0) {
                nums[remove_index] = nums[index];
                ++remove_index;
            }
        }
        return remove_index > 0 ? remove_index : nums.size();
    }
};