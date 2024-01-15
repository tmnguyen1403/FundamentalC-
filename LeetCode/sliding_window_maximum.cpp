#include <deque>

class Solution {
public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
        std::vector<int> result;
        std::deque<int> max_deque;

        for (int i = 0;i < nums.size();++i)
        {
            //remove element out of window range
            while (max_deque.size() > 0 && max_deque.front() < i +1 - k) {
                max_deque.pop_front();
            }
            //remove element smaller than current number to maintain the invariant that the deque is none-increasing
            while (max_deque.size() > 0 && nums[max_deque.front()] < nums[i]) {
                max_deque.pop_back();
            }
            max_deque.push_back(i);
            if (i >= k - 1)
                result.push_back(nums[max_deque.front()]);
        }
        return result;
    }
};