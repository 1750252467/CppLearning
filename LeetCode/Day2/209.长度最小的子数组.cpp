/*
 * @lc app=leetcode.cn id=209 lang=cpp
 * @lcpr version=21801
 *
 * [209] 长度最小的子数组
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
    int minSubArrayLen(int target, vector<int>& nums) {

        int result = INT32_MAX;
        int sum = 0;
        int i = 0 ;
        int subLength = 0;
        for(int j = 0; j < nums.size(); ++j) {

            sum += nums[j];
            while(sum >= target) {

                subLength = j-i+1;

                result = result < subLength ? result : subLength;
                
                sum -= nums[i++];
            } 
            
        }
        return result == INT32_MAX ? 0 : result;

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
// 7\n[2,3,1,2,4,3]\n
// @lcpr case=end

// @lcpr case=start
// 4\n[1,4,4]\n
// @lcpr case=end

// @lcpr case=start
// 11\n[1,1,1,1,1,1,1,1]\n
// @lcpr case=end

 */


