/*
 * @lc app=leetcode.cn id=343 lang=cpp
 * @lcpr version=21907
 *
 * [343] 整数拆分
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
    int integerBreak(int n) {
        vector<int> dp(n+1);
        dp[2] = 1;
        for(int i = 3; i <= n; ++i) {
            for(int j = 1; j <= i/2; ++j) {
                dp[i] = max(dp[i],max((i-j) * j,dp[i-j]*j));
            }
        }
        return dp[n];
    }
};
// @lc code=end



/*
// @lcpr case=start
// 2\n
// @lcpr case=end

// @lcpr case=start
// 10\n
// @lcpr case=end

 */

