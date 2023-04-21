/*
 * @lc app=leetcode.cn id=746 lang=cpp
 * @lcpr version=21906
 *
 * [746] 使用最小花费爬楼梯
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
    int minCostClimbingStairs(vector<int>& cost) {
       vector<int> dp(cost.size()+1);
       dp[0] = 0;
       dp[1] = 0;
       for(int i = 2; i <= cost.size();i++) {
        dp[i] = min(dp[i-1]+cost[i-1],dp[i-2]+cost[i-2]); 
       }
       return dp[cost.size()];
    }
};
// @lc code=end



/*
// @lcpr case=start
// [10,15,20]\n
// @lcpr case=end

// @lcpr case=start
// [1,100,1,1,1,100,1,1,100,1]\n
// @lcpr case=end

 */

