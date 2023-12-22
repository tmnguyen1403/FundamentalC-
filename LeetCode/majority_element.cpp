/*
Using Boyer-moore algo
the majority element frequency is greater than N/2
For N is the total number of elements
*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
       int major = nums[0];
       int count = 1;
       for (auto iter = nums.begin()+1; iter != nums.end(); ++iter) {
           if (count == 0) {
               major = *iter;
               count = 1;
           }
           else if (major == *iter)
                ++count;
            else
                --count;
       }
       return major;
    }
};