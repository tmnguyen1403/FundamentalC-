/*
You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.

You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.

Return the answers to all queries. If a single answer cannot be determined, return -1.0.

Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.

Note: The variables that do not occur in the list of equations are undefined, so the answer cannot be determined for them.

 

Example 1:

Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Explanation: 
Given: a / b = 2.0, b / c = 3.0
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
note: x is undefined => -1.0
Example 2:

Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
Output: [3.75000,0.40000,5.00000,0.20000]
Example 3:

Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
Output: [0.50000,2.00000,-1.00000,-1.00000]
 

Constraints:

1 <= equations.length <= 20
equations[i].length == 2
1 <= Ai.length, Bi.length <= 5
values.length == equations.length
0.0 < values[i] <= 20.0
1 <= queries.length <= 20
queries[i].length == 2
1 <= Cj.length, Dj.length <= 5
Ai, Bi, Cj, Dj consist of lower case English letters and digits.
*/
#include <iostream>
#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>

class Solution {
public:
    std::vector<std::vector<double>> adjacency{};
    double calcEquationDFS(const int& index_a, const int& index_b, std::vector<bool>& visited) {
        if (adjacency[index_a][index_b] != 0.0)
            return adjacency[index_a][index_b];

        double final_result = -1.0;
        visited[index_a] = true;
        for (int index = 0; index < adjacency[index_a].size(); ++index) {
            if (visited[index] || adjacency[index_a][index] == 0.0)
                continue;
            visited[index] = true;
            double result_path = calcEquationDFS(index, index_b, visited);
            if (result_path != -1.0) {
                final_result = adjacency[index_a][index] * result_path;
                adjacency[index_a][index_b] = final_result;
                adjacency[index_b][index_a] = 1 / final_result;
                visited[index] = false;
                break;
            }
            visited[index] = false;
        }
        //a,b - b-a? -1?//found the path return the value otherwise return -1.0;
        return final_result;
    }

    std::vector<double> calcEquation(std::vector<std::vector<std::string>>& equations, std::vector<double>& values, std::vector<std::vector<std::string>>& queries) {
        //build the map the convert string variable to integer index for the adjacency matrix
        std::unordered_map<std::string_view, int> variable_indices;
        int index = 0;
        for (const auto& equation: equations) {
            for (const auto& variable : equation) {
                if (variable_indices.find(variable) == variable_indices.end()) {
                    variable_indices[variable] = index;
                    ++index;
                }
            }
        }
        //build the adjacency matrix
        
        int matrix_size = index;
        {
           
            adjacency.resize(matrix_size);
            for (auto row = 0; row < matrix_size; ++row) {
                adjacency[row].resize(matrix_size);
                for (auto col = 0; col < matrix_size; ++col) {
                    adjacency[row][col] = 0.0;//None existing path
                    if (row == col) 
                        adjacency[row][col] = 1.0;
                }
            }
        }
        //Populate with queries value
        {
            for (auto index = 0; index < equations.size(); ++index) {
                //get variable index from an equation
                auto equation = equations[index];
                auto a = equation[0];
                auto b =  equation[1];
                auto index_a = variable_indices[a];
                auto index_b = variable_indices[b];

                auto ab_value = values[index];
                adjacency[index_a][index_b] = ab_value;
                adjacency[index_b][index_a] = 1 / ab_value;
            }
        }
        //use DFS to check for the existing path in a query
        auto result = std::vector<double>{};

        for (const auto& query: queries) {
            auto a = query[0];
            auto b =  query[1];
            auto index_a = -1;
            auto index_b = -1;
            if (variable_indices.find(a) != variable_indices.end())
                index_a = variable_indices[a];
            if (variable_indices.find(b) != variable_indices.end())
                index_b = variable_indices[b];
            if (index_a == -1 || index_b == -1) {
                result.push_back(-1.0);
                continue;
            }
            //find path to result
            std::vector<bool> visited;
            visited.resize(matrix_size);
            auto query_result = calcEquationDFS(index_a, index_b, visited);
            result.push_back(query_result);
        }
        // A/C = A/B * B/C (exist)
        return result;
    }
};