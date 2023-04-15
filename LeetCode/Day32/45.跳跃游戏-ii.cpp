/*
 * @lc app=leetcode.cn id=45 lang=cpp
 * @lcpr version=21906
 *
 * [45] 跳跃游戏 II
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
    int jump(vector<int>& nums) {
        int curDistence = 0;
        int ans = 0;
        int nextDistance = 0;
        for(int i = 0; i < nums.size()-1; ++i) {
            nextDistance = max(nums[i]+i, nextDistance);
            if(i == curDistence) {
                curDistence = nextDistance;
                ans++;
            }
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,1,1,4]\n
// @lcpr case=end

// @lcpr case=start
// [2,3,0,1,4]\n
// @lcpr case=end

 */

