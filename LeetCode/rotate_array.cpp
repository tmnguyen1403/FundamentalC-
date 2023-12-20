#include <vector>
#include <iostream>

using namespace std;
class Solution {
public:
/*
Solution explain:
The rotate position can be calculated using rotate_pos=(current + k) % n
We can then use the calculated rotate position as the next position to continue moving
in the nums array.
Eventually, we will return to the starting position.
The first scenario:
1. We rotated all numbers in the array and return to the original starting position.
 --> we updated the starting position and finish
2. We rotated n-x numbers and return to the original starting position.
 --> we increase the starting position by 1 and continue using the same rotation scheme
 Why increase by 1?
 Let i be the starting position index
 Let s be the the number of rotations
 Let k be the steps
 Let N b the size of the array.
 If i + 1 is visited, i < i + 1 < k, then:
 (i + sk) = i + 1 (mod N)
 Let q be the quotion of (i + sk)/N,then:
 Nq + i + 1 = i + xk
 Nq + 1 = xk (1)
 If there exists two positive integers q and k that satisfy (1),
 then:
 Nq + 1 + m = xk + m, for all none-negative integer m.
 Meaning that there exists s satisfies:
 (i + sk) = i + 1 + m (mod N) (2)
 From (2), all positions must be rotated before returning to the starting position.
 Otherwise, repeating the same rotation scheme for the same starting position
will keep yielding the same result.
 
 Therefore, if all positions are not visited and we are back at the starting position,
 then i + 1 is not visited either.
 In fact, i < i + m < i + k will become the starting point using the above reasoning 

*/
    void rotate(vector<int>& nums, int k) {
        //No rotation
        if (k == 0 || k % nums.size() == 0)
            return;
        int n = nums.size();
        int start_index = 0;
        int next_index = 0;
        int first_num = nums[start_index];
        for (int step = 0; step < n;++step) {
            //calculate the index to rotate the current number
            next_index = (next_index + k) % n;
            int second_num = nums[next_index];
            nums[next_index] = first_num;
            first_num = second_num;
            
            //increase the index by 1 since we are going back to the beginning
            if (next_index == start_index && step < n) {
                start_index += 1;
                first_num = nums[start_index];
                next_index = start_index;
            }
        }

    }
};

int main() 
{
    vector<int> nums{1,2,3,4,5,6,7};
    for (auto num: nums) {
        cout << num << " ";
    }
    cout << endl;
    int k = 3;
    Solution s;
    s.rotate(nums,k);

     for (auto num: nums) {
        cout << num << " ";
    }
    {
        vector<int> nums{-1,-100,3,99};
        cout << endl;
        for (auto num: nums) {
            cout << num << " ";
        }
        int k = 2;
        s.rotate(nums,k);

        for (auto num: nums) {
            cout << num << " ";
        }
        cout << endl;
    }

}