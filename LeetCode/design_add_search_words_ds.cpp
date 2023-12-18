/*
This is a Trie but the only different is when search the word
We have to consider the . which requires us to iterate through all nodes in the current Trie
// Checking for leaves also requires iterate through all the leaves if possible
// If search frequently, might be using unodered_map to boost the check for .
*/
#include <string>
#include <string_view>
#include <array>
#include <set>

class Trie {
private:
    std::array<Trie*, 26> letters{nullptr};
    std::set<char> leaf_nodes{};

public:    
    Trie(){}
    ~Trie(){
        for (auto& node : letters) {
            if (node != nullptr) {
                delete node;
                node = nullptr;
            }
        }
    }
    
    void insert(std::string word) {
        insert_view(word);
    }

    void insert_view(std::string_view word) {
        int char_index = word[0] - 'a';
        if (word.length() == 1) {
            leaf_nodes.emplace(word[0]);
        }
        if (letters[char_index] == nullptr) {
            letters[char_index] = new Trie();
        }
        letters[char_index]->insert_view(word.begin()+1);
    }
    
    bool search(std::string word) {
        return search_view(word);
    }

    bool search_view(std::string_view word) {
        if (word[0] == '.') {
            return search_view_dot(word);
        }
        int char_index = word[0] - 'a';
        if (word.length() == 1) {
            return leaf_nodes.contains(word[0]);
        }
        if (letters[char_index] != nullptr) {
            return letters[char_index]->search_view(word.begin() + 1);
        }
        return false;
    }

    bool search_view_dot(std::string_view word) {
        //We know that the first char is the dot
        bool result = false;
        if (word.length() == 1) {
            //Any leaf nodes result to true
            return leaf_nodes.size() > 0;
        } else {
            auto tmp_result = false;
            for (const auto& letter : letters) {
                if (letter != nullptr)
                    tmp_result = letter->search_view(word.begin() + 1);
                if (tmp_result == true) {
                    result = true;
                    break;
                }
            }
        }
        return result;
    }
    
    bool startsWith(std::string prefix) {
        return startsWith_view(prefix);
    }

    bool startsWith_view(std::string_view prefix) {
        int char_index = prefix[0] - 'a';
        if (prefix.length() == 1) {
            return leaf_nodes.contains(char_index) || letters[char_index] != nullptr;
        }
        if (letters[char_index] != nullptr) {
            return letters[char_index]->startsWith_view(prefix.begin() + 1);
        }
        return false;
    }
};

class WordDictionary {
private:
    Trie trie; 
public:
    WordDictionary() {
        
    }
    
    void addWord(std::string word) {
        trie.insert_view(word);
    }
    
    bool search(std::string word) {
        return trie.search_view(word);
    }
};