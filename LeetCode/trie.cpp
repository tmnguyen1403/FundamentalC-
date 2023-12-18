#include <array>
#include <string_view>

class Trie {
std::array<Trie*, 26> letters{nullptr};
std::array<bool, 26> leaf_nodes{false};

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
            leaf_nodes[char_index] = true;
            return;
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
        int char_index = word[0] - 'a';
        if (word.length() == 1) {
            return leaf_nodes[char_index];
        }
        if (letters[char_index] != nullptr) {
            return letters[char_index]->search_view(word.begin() + 1);
        }
        return false;
    }
    
    bool startsWith(std::string prefix) {
        return startsWith_view(prefix);
    }

    bool startsWith_view(std::string_view prefix) {
        int char_index = prefix[0] - 'a';
        if (prefix.length() == 1) {
            return leaf_nodes[char_index] || letters[char_index] != nullptr;
        }
        if (letters[char_index] != nullptr) {
            return letters[char_index]->startsWith_view(prefix.begin() + 1);
        }
        return false;
    }
};