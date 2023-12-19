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
#include <mutex>
#include <thread>

class Trie
{
private:
    std::array<Trie*, 26>  nodes{}; //This need to be initialized with nullptr
    std::set<char> leaves;
    std::mutex mutex_leaves;
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
        {
            std::lock_guard lock{mutex_leaves};
            auto iter = leaves.find(c);
            //Erasing the char from leaves so that we don't generate duplicate result
            //Ideally, we should not modify the state of the Trie while searching so that we can perform parallel search instead
            //
            if (iter != leaves.end()) {
                is_leave = true;
                leaves.erase(iter);
            }
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
    std::vector<std::string> result_{};
    char flag_{'.'};
    Trie* root; 
    std::mutex mutex_result_;
public:
    Solution() {
        root = new Trie();
        result_.clear();
    }
    ~Solution() {
        delete root;
    }

    void searchNeighbor(const std::vector<std::vector<char>>& board, int row, int col, Trie* current_head, std::string current_word, std::vector<std::vector<bool>>& visited) {
        if (current_head == nullptr)
            return;

        auto nb_rows = board.size();
        auto nb_cols = board[0].size();
        for (const auto& direction: directions_) {
                auto [x,y] = direction;
                auto nRow = row + x;
                auto nCol = col + y;
                //Index validation
                if (nRow < 0 || nRow >= nb_rows || nCol < 0 || nCol >= nb_cols)
                    continue;
                //Visited validation
                if (visited[nRow][nCol])
                    continue;
                visited[nRow][nCol] = true;
                char nChar = board[nRow][nCol];
                
                auto [is_leaf, next_head] = current_head->endWith(nChar);
                std::string next_word = current_word + nChar;
                if (is_leaf) {
                    //build world

                    std::lock_guard lock{mutex_result_};
                    result_.push_back(next_word);
                }
                if (next_head != nullptr) {
                    searchNeighbor(board, nRow, nCol, next_head, next_word, visited);
                }
                visited[nRow][nCol] = false;
            }
    }

    std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
        //First build Trie from the words that we need to search
        for (const auto& word: words) {
            root->add(word);
        }
        auto nb_rows = board.size();
        auto nb_cols = board[0].size();
        
        std::tuple<int,int,int,int> position1 {0,nb_rows/2,0,nb_cols};
        helper(board, words, position1);
        std::thread thread1(&Solution::helper,this, std::ref(board), std::ref(words),  std::ref(position1));
       
        std::tuple<int,int,int,int> position2 {nb_rows/2,nb_rows,0,nb_cols};
        std::thread thread2(&Solution::helper, this, std::ref(board), std::ref(words),  std::ref(position2));
        thread1.join();
        thread2.join();
        // std::tuple<int,int,int,int> positionAll {0,nb_rows,0,nb_cols};

        // helper(board, words, positionAll);

        auto result_copy = result_;
        //result_.clear();
        return result_copy;
    }

    //This is the helper function allow to cal in multiple threads
    void helper(const std::vector<std::vector<char>>& board, const std::vector<std::string>& words, const std::tuple<int,int,int,int>& positions) {     
        auto nb_rows = board.size();
        auto nb_cols = board[0].size();

        std::vector<std::vector<bool>> visited;
        visited.resize(nb_rows);
        for (auto& row: visited) {
            row.resize(nb_cols);
            std::fill(row.begin(), row.end(), false);
        }
        auto [start_row, end_row, start_col, end_col] = positions;

        for (auto row = start_row; row < end_row; ++row) {
            for (auto col = start_col; col < end_col; ++col) {

                if (visited[row][col])
                    continue;
                const char c = board[row][col];
                visited[row][col] = true;
                //Find neighbor
                auto [is_leaf, next_node] = root->endWith(c);
                std::string word{c};
                if (is_leaf)
                    result_.push_back(word);
                if (next_node != nullptr) {
                    searchNeighbor(board,row, col, next_node, word, visited);
                }
                visited[row][col] = false;
            }
        }
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
        words.resize(5);
        words[0] = "oath";
        words[1] = "pea";
        words[2] = "eat";
        words[3] = "rain";
        words[4] = "o";


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