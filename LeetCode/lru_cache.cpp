#include <unordered_map>
#include <map>

using keytime = std::tuple<int,int>;

struct keytime_compare {
    bool operator()(const keytime& a, const keytime& b) const {
        auto timeA = std::get<1>(a);
        auto timeB = std::get<1>(b);
        return timeA < timeB;
    }
};

class LRUCache {

int capacity_;
std::map<keytime,int,keytime_compare> values;//map key to the index in the deque?
std::unordered_map<int, int> key_time;//map key to the index in the deque?
int access_time{0}; 

public:
    LRUCache(int capacity) : capacity_{capacity}, values{keytime_compare()} {
    
    }
    
    int get(int key) {
        //build the key-time
        auto timeIt = key_time.find(key);
        if (timeIt == key_time.end())
            return -1;
        auto timeValue = timeIt->second;
        auto kt = keytime(key, timeValue);
        auto valIt = values.find(kt);
        //extract node to update access time
        auto node = values.extract(valIt);
        ++access_time;
        auto newKt = std::make_tuple(key, access_time);
        auto returnValue = node.mapped();
        //update keytime in the values map
        node.key() = newKt;
        values.insert(std::move(node));
        //update access time in the map
        key_time[key] = access_time;

        return returnValue;
    }
    
    void put(int key, int value) {
        //check if element already exist
        auto it = key_time.find(key);
        //if this is a update key, we don't need to remove
        if (it == key_time.end() && values.size() >= capacity_)
        {
            //need to remove the LRU element
            auto vIt = values.begin();
            auto k = std::get<0>(vIt->first);
            values.erase(values.begin());
            key_time.erase(k);
        }
        ++access_time;
        //update existing
        if (it != key_time.end()) {
            auto current_time = it->second;
            auto kt = keytime(key,current_time);
            auto node = values.extract(kt);
            auto newKey = keytime(key,access_time);
            node.key() = newKey;
            node.mapped() = value;
            values.insert(std::move(node));
        }
        //insert new element 
        else {
            auto kt = keytime(key,access_time);
            values[kt] = value;
        }
        key_time[key] = access_time;
    }
};
