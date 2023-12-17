/*
Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.
*/
#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <queue>
using namespace std;
class Solution {
public:
    //DFS Visit
    //Marking array
    //neighborhood calculation
    using direction = std::tuple<int,int>;
    std::array<direction,4> neighbor_directions {
    std::make_tuple(0,-1),{0,1},{-1,0},{1,0}
    };

    /*
    DFS Approach
    */
    void surveyLandDFS(const vector<vector<char>>& grid, const int& row, const int& col)
    {
        int num_rows = grid.size();
        int num_cols = grid[0].size();

        for (const auto& [x,y]: neighbor_directions) {
            int neighbor_row = row + x;
            int neighbor_col = col + y;
            if (neighbor_row < 0 || neighbor_row >= num_rows || neighbor_col < 0 || neighbor_col >= num_cols) {
                //Invalid neighbor
                continue;
            }
            if (visited[neighbor_row][neighbor_col] || grid[neighbor_row][neighbor_col] == '0')
                continue;
            visited[neighbor_row][neighbor_col] = true;
            surveyLandDFS(grid, neighbor_row, neighbor_col);
        }
    }

    /*
    BFS Approach
    */
    void surveyLandBFS(const vector<vector<char>>& grid, const int& row, const int& col)
    {
        int num_rows = grid.size();
        int num_cols = grid[0].size();
        using neighbor = std::tuple<int,int>;
        std::queue<neighbor> neighbors;

        auto getNeighbors = [&](const int& row, const int& col) {
            for (const auto& [x,y]: neighbor_directions) {
                int neighbor_row = row + x;
                int neighbor_col = col + y;
                if (neighbor_row < 0 || neighbor_row >= num_rows || neighbor_col < 0 || neighbor_col >= num_cols) {
                    //Invalid neighbor
                    continue;
                }
                if (visited[neighbor_row][neighbor_col] || grid[neighbor_row][neighbor_col] == '0')
                    continue;
                //Has to mark visited here, otherwise the neighbor will be added when we are visiting from other neighbors
                visited[neighbor_row][neighbor_col] = true;
                neighbors.push(std::make_tuple(neighbor_row,neighbor_col));            
            }
        };
        //Visit all possible neighbor 
        getNeighbors(row, col);
        while (!neighbors.empty())
        {
            auto [nrow,ncol] = neighbors.front();
            neighbors.pop();
            
            getNeighbors(nrow,ncol);
        }
    }

    void surveyLandBFSWithoutExtraMemory(vector<vector<char>>& grid, const int& row, const int& col)
    {
        int num_rows = grid.size();
        int num_cols = grid[0].size();
        using neighbor = std::tuple<int,int>;
        std::queue<neighbor> neighbors;

        auto getNeighbors = [&](const int& row, const int& col) {
            for (const auto& [x,y]: neighbor_directions) {
                int neighbor_row = row + x;
                int neighbor_col = col + y;
                if (neighbor_row < 0 || neighbor_row >= num_rows || neighbor_col < 0 || neighbor_col >= num_cols) {
                    //Invalid neighbor
                    continue;
                }
                if (grid[neighbor_row][neighbor_col] == '0')
                    continue;
                //Has to mark visited here, otherwise the neighbor will be added when we are visiting from other neighbors
                grid[neighbor_row][neighbor_col] = '0';
                neighbors.push(std::make_tuple(neighbor_row,neighbor_col));            
            }
        };
        //Visit all possible neighbor 
        getNeighbors(row, col);
        while (!neighbors.empty())
        {
            auto [nrow,ncol] = neighbors.front();
            neighbors.pop();
            getNeighbors(nrow,ncol);
        }
    }



    int numIslands(vector<vector<char>>& grid) {
        //Two options to solve and they should yield the same result
        auto n1 = numIslandsNoAuxilary(grid);
        auto n2 = numIslandsAuxilary(grid);
        return n1;
    }

    int numIslandsAuxilary(vector<vector<char>>& grid) {
        //iterate through the iland
        //when encounter a land, start scanning the neighbor
        //either using DFS or BFS to mark the the neighbors to be visited
        //when marking complete, increase the island count by 1
        //Init the visited
        auto num_rows = grid.size();
        auto num_cols = grid[0].size();

        /*
        Using auxilary array to mark visited
        */
        visited.resize(num_rows);
        for (auto index = 0; index < num_rows; ++index) {
            visited[index].resize(num_cols);
            for (auto i = 0; i < num_cols; ++i)
                visited[index][i] = false;
        }
        int total_islands = 0;
        //Search for land
        for (auto row = 0; row < num_rows; ++row) {
            for (auto col = 0; col < num_cols; ++col) {
                if (grid[row][col] == '1' && !visited[row][col]) {
                    visited[row][col] = true;
                    surveyLandDFS(grid, row, col);
                    ++total_islands;
                }
            }
        }
        visited.clear();
        return total_islands;
    }


    int numIslandsNoAuxilary(vector<vector<char>>& grid) {
        //iterate through the iland
        //when encounter a land, start scanning the neighbor
        //either using DFS or BFS to mark the the neighbors to be visited
        //when marking complete, increase the island count by 1
        //Init the visited
        auto num_rows = grid.size();
        auto num_cols = grid[0].size();

        int total_islands = 0;
        //Search for land
        for (auto row = 0; row < num_rows; ++row) {
            for (auto col = 0; col < num_cols; ++col) {
                if (grid[row][col] == '1') {
                    grid[row][col] = '0';
                    surveyLandBFSWithoutExtraMemory(grid, row, col);
                    ++total_islands;
                }
            }
        }
        return total_islands;
    }
    vector<vector<bool>> visited; 
};