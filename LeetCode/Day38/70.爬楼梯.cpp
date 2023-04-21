/*
 * @lc app=leetcode.cn id=70 lang=cpp
 * @lcpr version=21906
 *
 * [70] 爬楼梯
 */

// @lc code=start
class Solution {
public:
    int climbStairs(int n) {
        int dp[2];
        dp[0] = 1;
        dp[1] = 2;
        if(n<=2) return n;
        for(int i = 3;i <=n; ++i){
            int sum = dp[0] +dp[1];
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

 */

