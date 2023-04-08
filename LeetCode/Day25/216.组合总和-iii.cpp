/*
 * @lc app=leetcode.cn id=216 lang=cpp
 * @lcpr version=21902
 *
 * [216] 组合总和 III
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
    void backtracking(int targetSum,int k,int sum,int startIndex) {
        if(sum > targetSum) {
            return;
        }
        if(path.size() == k) {
            if(sum == targetSum) result.push_back(path);
            return;
        }

        for(int i = startIndex; i <= 9 -(k-path.size())+1;i++) {
            sum += i;
            path.push_back(i);
            backtracking(targetSum,k,sum,i+1);
            sum -= i;
            path.pop_back(); 
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {

    }
};
// @lc code=end



/*
// @lcpr case=start
// 3\n7\n
// @lcpr case=end

// @lcpr case=start
// 3\n9\n
// @lcpr case=end

// @lcpr case=start
// 4\n1\n
// @lcpr case=end

 */


