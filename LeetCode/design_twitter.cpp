#include <unordered_map>
#include <map>
#include <unordered_set>
#include <queue>

class Twit {
private:
    int tweetId_;
    uint64_t timestamp_;
public:
    Twit(int tweetId, uint64_t timestamp) : tweetId_{tweetId}, timestamp_{timestamp} {}
    auto getTweetId() const {return tweetId_;}
    auto getTimestamp() const {return timestamp_;}
    bool operator<(const Twit& other) const {
        return timestamp_ < other.timestamp_;
    }
    bool operator>(const Twit& other) const {
        return timestamp_ > other.timestamp_;
    }
};

class Twitter {
private:
    std::unordered_map<int, std::vector<Twit>> user_tweets;
    std::unordered_map<int, std::unordered_set<int>> followees;
    uint64_t timestamp_{0};
    int maxTweet_{10};
public:
    Twitter() {
        
    }
    
    //how to save tweet to reflect most recent to least recent?
    //for each userID, vector with time,tweetId
    //we need a timestamp that increase whenever a tweet is post
    void postTweet(int userId, int tweetId) {
        user_tweets[userId].push_back(Twit(tweetId, timestamp_));
        ++timestamp_;
        if (followees.find(userId) == followees.end()) {
            followees[userId].insert(userId);
        }
    }
    
    vector<int> getNewsFeed(int userId) {
        //using a priority queue (min heap) to store 10 tweets (most recent first)
        std::priority_queue<Twit,std::vector<Twit>, std::greater<>> q;
        const auto& user_followees = followees[userId];
        for (auto id : user_followees) {
            if (user_tweets.find(id) != user_tweets.end()) {                
                const auto& tweets = user_tweets[id];
                auto end = tweets.size() - 1;
                int start = end >= maxTweet_ ? end - maxTweet_ + 1 : 0;
                for (;start <= end; ++start) {
                    q.push(tweets[start]);
                    if (q.size() > maxTweet_)
                        q.pop();
                }
            }
        }
        //create result
        std::vector<int> result;
        result.resize(q.size());
        for (auto index = result.size(); index > 0; --index) {
            auto tweetId = (q.top()).getTweetId();
            result[index-1] = tweetId;
            q.pop();
        }
        return result;
   }
    //need to map the followerID to followees (one to many)
    //map, set
    /*
     The user with ID followerId started following the user with ID followeeId
    */
    void follow(int followerId, int followeeId) {
        if (followees.find(followerId) == followees.end()) {
            followees[followerId].insert(followerId);
        }
        followees[followerId].insert(followeeId);
    }
    // The user with ID followerId started unfollowing the user with ID followeeId.
    void unfollow(int followerId, int followeeId) {
        auto pos = followees[followerId].find(followeeId);
        if (pos != followees[followerId].end()) {
            followees[followerId].erase(pos);
        } 
    }
};