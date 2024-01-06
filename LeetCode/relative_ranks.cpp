#include <queue>
#include <string>
#include <tuple>
#include <vector>
class Solution {
public:
    std::string getRankStr(int rank) {
        switch (rank) {
            case 0:
                return "Gold Medal";
            case 1:
                return "Silver Medal";
            case 2:
                return "Bronze Medal";
            default:
                return std::to_string(rank+1);
        }
    }
    std::vector<std::string> findRelativeRanks(std::vector<int>& score) {
        //use max heap (priority queue) to store the score and index of each atlethe
        using ranks = std::vector<std::tuple<int,int>>;
        auto compare = [](auto a, auto b) {
            return std::get<0>(a) < std::get<0>(b);
        };

        std::priority_queue<std::tuple<int,int>,ranks, decltype(compare)> q{compare,ranks{}};
        for (int index=0; index<score.size();++index) {
            q.push(std::make_tuple(score[index],index));
        }
        std::vector<std::string> result;
        result.resize(score.size());
        for (int rank = 0; rank < score.size(); ++rank) {
            auto [pScore,pIndex] = q.top();
            q.pop();
            result[pIndex] = getRankStr(rank); 
        }
        return result;
    }
};


/*
Solved by using dictionary, why is it slower and consume more memory?
*/
#include <unordered_map>

class Solution {
public:
    std::string getRankStr(int rank) {
        switch (rank) {
            case 0:
                return "Gold Medal";
            case 1:
                return "Silver Medal";
            case 2:
                return "Bronze Medal";
            default:
                return std::to_string(rank+1);
        }
    }
    vector<string> findRelativeRanks(vector<int>& score) {
        //use unordered_map to store position
        std::unordered_map<int,size_t> positions;
        for (auto index = 0; index < score.size();++index) {
            positions[score[index]] = index;
        }
        //sort the score by descending order
        std::sort(score.begin(), score.end(), std::greater<>{});
        std::vector<std::string> result;
        result.resize(score.size());
        for (int rank = 0; rank < score.size(); ++rank) {
            result[positions[score[rank]]] = getRankStr(rank); 
        }
        return result;
    }
};