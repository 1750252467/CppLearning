/*
 * @lc app=leetcode.cn id=198 lang=cpp
 * @lcpr version=21907
 *
 * [198] 打家劫舍
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
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        if(nums.size() == 1) return nums[0];
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        dp[1] = max(nums[0],nums[1]);
        for(int i = 2; i < nums.size(); i++) {
            dp[i] = max(dp[i-2] + nums[i],dp[i-1]);
        }
        return dp[nums.size()-1];
        
     }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,1]\n
// @lcpr case=end

// @lcpr case=start
// [2,7,9,3,1]\n
// @lcpr case=end

 */

