/*
Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 

Example 1:


Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]

Example 2:
Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []
*/
#include <iostream>
#include <string>
#include <set>
#include <array>
#include <string_view>
#include <tuple>
#include <vector>
#include <numeric>

class Trie
{
private:
    std::array<Trie*, 26>  nodes{}; //This need to be initialized with nullptr
    std::set<char> leaves;
public:
    Trie(){}
    ~Trie(){
        for (auto& node: nodes) {
            if (node != nullptr)
                delete node;
            node = nullptr;
        }
    }
    void add(std::string_view word) {
        if (word.length() == 1) {
            if (!leaves.contains(word[0]))
                leaves.emplace(word[0]);
            return;
        }
        int index = word[0] - 'a';
        if (nodes[index] == nullptr) {
            nodes[index] = new Trie();
        }
        nodes[index]->add(word.begin() + 1);
    }

    //Custom startWith for the problem

    auto endWith(const char& c) -> std::tuple<bool, Trie*> {
        bool is_leave = false;
        auto iter = leaves.find(c);
        //Erasing the char from leaves so that we don't generate duplicate result
        //Ideally, we should not modify the state of the Trie while searching so that we can perform parallel search instead
        //
        if (iter != leaves.end()) {
            is_leave = true;
            leaves.erase(iter);
        }
        int index = c - 'a';
        auto next_node = nodes[index];
        return std::make_tuple(is_leave, next_node);
    }
};

class Solution {
private:
    std::array<std::tuple<int,int>,4> directions_ {
        std::make_tuple(0,-1),
        {-1,0},
        {0,1},
        {1,0}
    };
    std::vector<std::string> result_;
    char flag_{'.'};
public:

    void searchNeighbor(std::vector<std::vector<char>>& board, int row, int col, Trie* current_head, std::string current_word) {
        if (current_head == nullptr)
            return;

        auto nb_rows = board.size();
        auto nb_cols = board[0].size();
        for (const auto& direction: directions_) {
                auto [x,y] = direction;
                auto nRow = row + x;
                auto nCol = col + y;
                //Index validation
                //std::cout << nRow << " " << nCol << " \n";
                if (nRow < 0 || nRow >= nb_rows || nCol < 0 || nCol >= nb_cols)
                    continue;
                //std::cout <<"Pass Validation: " << nRow << " " << nCol << " \n";
                //Visited validation
                if (board[nRow][nCol] == flag_)
                    continue;
                //std::cout <<"Pass Validation 2 " << nRow << " " << nCol << " \n";
                
                char nChar = board[nRow][nCol];
                board[nRow][nCol] = flag_;  
                auto [is_leaf, next_head] = current_head->endWith(nChar);
                std::string next_word = current_word + nChar;
                if (is_leaf) {
                    //build world
                    result_.push_back(next_word);
                }
                if (next_head != nullptr) {
                    searchNeighbor(board, nRow, nCol, next_head, next_word);
                }
                board[nRow][nCol] = nChar;  
            }
    }

    std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
        Trie* root = new Trie(); 
        //First build Trie from the words that we need to search
        for (const auto& word: words) {
            root->add(word);
        }
        auto nb_rows = board.size();
        auto nb_cols = board[0].size();

        //left,up,right,down


        for (auto row = 0; row < nb_rows; ++row) {
            for (auto col = 0; col < nb_cols; ++col) {
                //Need a visited mark
                //std::cout << row << " " << col << " \n";
                if (board[row][col] == flag_)
                    continue;
                const char c = board[row][col];
                board[row][col] = flag_;
                //Find neighbor
                auto [is_leaf, next_node] = root->endWith(c);
                std::string word{c};
                if (is_leaf)
                    result_.push_back(word);
                if (next_node != nullptr) {
                    searchNeighbor(board,row, col, next_node, word);
                }
               board[row][col] = c;
            }
        }
        auto result_copy = result_;
        result_.clear();
        delete root;
        return result_copy;
    }
};


/*
Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
*/
int main()
{
    {
    std::vector<std::vector<char>> board;
    auto nrow = 4;
    auto ncol = 4;
    board.resize(nrow);
    board[0] = {'o','a','a','n'};
    board[1] = {'e','t','a','e'};
    board[2] = {'i','h','k','r'};
    board[3] = {'i','f','l','v'};

    std::vector<std::string> words;
    words.resize(4);
    words[0] = "oath";
    words[1] = "pea";
    words[2] = "eat";
    words[3] = "rain";

    Solution s;
    auto result = s.findWords(board, words);
    for (auto & s : result ) {
        std::cout << s << "\n";
    }
    }

    {
        std::vector<std::vector<char>> board;
        auto nrow = 2;
        auto ncol = 2;
        board.resize(nrow);
        board[0] = {'a','b'};
        board[1] = {'c','d'};

        std::vector<std::string> words;
        words.resize(1);
        words[0] = "abcb";

        Solution s;
        auto result = s.findWords(board, words);
        for (auto & s : result ) {
            std::cout << s << "\n";
        }
    }
    return 0;
}