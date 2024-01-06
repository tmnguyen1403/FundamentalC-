#include <queue>
#include <unordered_set>
#include <limits.h>

/*
Solve using priority queue
Time: O(nlogn)
Space: O(n)
Note: Overflow check
*/
class Solution {
public:
    int nthUglyNumber(int n) {
        if (n == 1)
            return 1;
        std::unordered_set<int> seen;
        //min heap
        std::priority_queue<int, std::vector<int>, std::greater<>> q;
        std::array<int,3> primes = {2,3,5};
        seen.insert(1);
        q.push(1);
        for (auto i = 0; i < n - 1; ++i) {
            int current = q.top();
            q.pop();
            for (int num : primes) {
                //overflow check
                if (current > INT_MAX / num)
                    continue;
                int next = current * num;
                if (seen.find(next) == seen.end()) {
                    q.push(next);
                    seen.insert(next);
                }
            }
        }
        return q.top();
    }
};

/*
Solve using DP
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    int nthUglyNumber(int n) {
        if (n == 1)
            return 1;
        
        std::vector<int> result;
        result.resize(n);
        std::array<int,3> primes = {2,3,5};
        std::array<int,3> prime_powers = {0,0,0};
        std::array<int,3> current_numers = {0,0,0};
        result[0] = 1;
        for (auto i = 1; i < n; ++i) {
            int current_prime_index = 0;
            current_numers[0] = result[prime_powers[0]]*primes[0];
            result[i] = current_numers[0];
            for (auto j = 1; j < 3; ++j) {
                current_numers[j] = result[prime_powers[j]]*primes[j];
                if (result[i] > current_numers[j]) {
                    result[i] = current_numers[j];
                }
            }
            for (auto j = 0; j < 3; ++j) {
                if (result[i] == current_numers[j])
                    prime_powers[j] += 1;
            }
        }
        return result[n-1];
    }
};