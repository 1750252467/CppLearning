/*
 * @lc app=leetcode.cn id=509 lang=cpp
 * @lcpr version=21906
 *
 * [509] 斐波那契数
 */

// @lc code=start
class Solution {
public:
    int fib(int n) {
        if(n <= 1) return n;
        int dp[2];
        dp[0] = 0;
        dp[1] = 1;
        for(int i = 2; i <= n; ++i) {
            int sum = dp[0] + dp[1];
            dp[0] = dp[1];
            dp[1] = sum;

        }
        return dp[1];
    }
};
// @lc code=end



/*
// @lcpr case=start
// 2\n
// @lcpr case=end

// @lcpr case=start
// 3\n
// @lcpr case=end

// @lcpr case=start
// 4\n
// @lcpr case=end

 */

