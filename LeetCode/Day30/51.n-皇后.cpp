/*
 * @lc app=leetcode.cn id=51 lang=cpp
 * @lcpr version=21906
 *
 * [51] N 皇后
 */
using namespace std;
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
// @lc code=start
class Solution {
private:
    vector<vector<string>> result;

    void backtracking(int n,int row,vector<string>& chessboard) {
        if(row == n) {
            result.push_back(chessboard);
            return;
        }

        for(int col = 0; col < n; col++) {
            if(isValid(row,col,chessboard,n)) {
                chessboard[row][col] = 'Q';
                backtracking(n,row + 1,chessboard);
                chessboard[row][col] = '.'; 
            }
        }
    }

    bool isValid(int row,int col,vector<string>& chessboard, int n) {

        for(int i = 0; i < row; ++i) {
            if(chessboard[i][col] == 'Q') {
                return false;
            }
        }

        for(int i = row - 1, j = col - 1; i >= 0 && j >= 0 ; i--,j--) {
            if(chessboard[i][j] == 'Q') {
                return false;
            }
        }

        for(int i = row - 1, j = col + 1; i >= 0 && j >=0; i--, j++) {
            if(chessboard[i][j] == 'Q') {
                return false;
            }
        }
        return true;
        }
public:
    vector<vector<string>> solveNQueens(int n) {
        result.clear();
        vector<string> chessboard(n,string(n,'.'));
        backtracking(n,0,chessboard);
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 4\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

 */

