/*
 * @lc app=leetcode.cn id=59 lang=cpp
 * @lcpr version=21801
 *
 * [59] 螺旋矩阵 II
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
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n,vector<int>(n,0));
        int startx = 0, starty = 0;
        int loop = n / 2;
        int mid = n / 2;
        int count = 1;
        int offset = 1;
        int i,j;
        while(loop--) {
            i = startx;
            j = starty;
            for(;j < n - offset; ++j) {
                res[startx][j] = count++;
            }
            for(;i < n - offset; ++i) {
                res[i][j] = count++;
            }
            for(;j > starty; --j) {
                res[i][j] = count++;
            }
            for(;i > startx; --i) {
                res[i][j] = count++;
            }
            if(n%2) {
                res[mid][mid] = count;
            }
            startx++;
            starty++;
            offset++;
        }
        if(n%2) {
                res[mid][mid] = count;
        }
        return res;
    }
};
// @lc code=end

// @lcpr-div-debug-arg-start
// funName=
// paramTypes= []
// returnType=
// @lcpr-div-debug-arg-end


/*
// @lcpr case=start
// 3\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

 */


