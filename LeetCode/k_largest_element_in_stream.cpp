#include <queue>
#include <vector>
class KthLargest {
private:
    std::priority_queue<int,std::vector<int>, std::greater<>> q;
    int k_;
public:
    KthLargest(int k, vector<int>& nums) 
    {
        k_ = k;
        for (auto num: nums) {
            q.push(num);
            if (q.size() > k_)
                q.pop();
        }
    }
    
    int add(int val) {
        q.push(val);
        while (q.size() > k_)
            q.pop();
        return q.top();
        //4,5,8
        //4,5,8
        //5,5,8
        //5,810
        //8,9,10
    }
};