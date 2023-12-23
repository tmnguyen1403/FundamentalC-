#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1)
            return s;
       string result;
       result.resize(s.length());
       // The number of elapsed character to get back to the same row
       int char_dist = (numRows - 1) * 2;
       auto result_iter = result.begin();
       for (int row = 0; row < numRows; ++row) {
           int s_index = row;
           while (s_index < s.length()) {
               *result_iter = s[s_index];
               ++result_iter;
                //First and last row will not have diagonal element
               if (row > 0 && row < numRows - 1) {
                   int diag_index = s_index + (numRows - row - 1) * 2;
                   if (diag_index < s.length()) {
                        *result_iter = s[diag_index];
                        ++result_iter;
                   }
               }
               s_index = s_index + char_dist; 
           } 
       }
       return result;
}    

int main() {
    Solution so;
    {
        std::string s{"PAYPALISHIRING"};
        std::cout << "length: " << s.length() << "\n";
        int numRows = 3; 
        auto result = so.convert(s,numRows);
        std::cout << "result: " << result << std::endl;
    }
        {
        std::string s{"PAYPALISHIRING"};
        std::cout << "length: " << s.length() << "\n";
        int numRows = 4; 
        auto result = so.convert(s,numRows);
        std::cout << "result: " << result << std::endl;
    }
}