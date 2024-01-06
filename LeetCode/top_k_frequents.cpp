#include <queue>
#include <unordered_map>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        std::unordered_map<int,int> freq;
        for (const auto& num : nums) {
            if (freq.find(num) == freq.end())
                freq[num] = 0;
            freq[num] += 1;
        }
        auto compare = [&](int a, int b) {
            return freq[a] < freq[b];
        };
        std::priority_queue<int,std::vector<int>,decltype(compare)> q(compare, std::vector<int>{});
        for (const auto& [key, val]: freq) {
            q.push(key);
        }
        std::vector<int> result;
        for(int i = 0; i < k; ++i) {
            result.push_back(q.top());
            q.pop();
        }
        return result;
    }
};

#include <queue>
#include <unordered_map>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        std::unordered_map<int,int> freq;
        for (const auto& num : nums) {
            if (freq.find(num) == freq.end())
                freq[num] = 0;
            freq[num] += 1;
        }
        auto compare = [&](int a, int b) {
            return freq[a] > freq[b];
        };
        std::priority_queue<int,std::vector<int>,decltype(compare)> q(compare, std::vector<int>{});
        for (const auto& [key, val]: freq) {
            q.push(key);
            /*always maintain k element in the min heap
            *the least frequent element will be removed
            *this allow better time complexity to be O(nlogk)
            */
            if (q.size() > k)
                q.pop();
        }
        std::vector<int> result;
        for(int i = 0; i < k; ++i) {
            result.push_back(q.top());
            q.pop();
        }
        return result;
    }
};