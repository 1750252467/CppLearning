/*
 * @lc app=leetcode.cn id=77 lang=cpp
 * @lcpr version=21902
 *
 * [77] 组合
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
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(int n,int k,int startIndex) {
        if(path.size() == k) {
            result.push_back(path);
            return;
        }

        for(int i = startIndex; i <= n -(k - path.size()) + 1; i++ ) {
            path.push_back(i);
            backtracking(n, k, i+1);
            path.pop_back();
        }
    }
    
public:
    vector<vector<int>> combine(int n, int k) {
        backtracking(n,k,1);
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 4\n2\n
// @lcpr case=end

// @lcpr case=start
// 1\n1\n
// @lcpr case=end

 */


