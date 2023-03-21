/*
 * @lc app=leetcode.cn id=15 lang=cpp
 * @lcpr version=21801
 *
 * [15] 三数之和
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
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(),nums.end());

        for(int i = 0; i < nums.size();++i){
            if(nums[i] > 0) {
                return result;
            }

            if(i > 0&& nums[i] == nums[i-1] ) {
                continue;
            }
            int left = i+1;
            int right = nums.size()-1;
            while(right > left) {

                if(nums[i] + nums[left] + nums[right] >0) right--;
                else if(nums[i] + nums[left] + nums[right] <0) left++; 
                else {
                    result.push_back(vector<int>{nums[i],nums[left],nums[right]});

                    while(right > left && nums[right] == nums[right-1]) right--;
                    while(right > left & nums[left] == nums[left+1]) left++;

                    right--;
                    left++;
                }
            }
        }
        return result;
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
// [-1,0,1,2,-1,-4]\n
// @lcpr case=end

// @lcpr case=start
// [0,1,1]\n
// @lcpr case=end

// @lcpr case=start
// [0,0,0]\n
// @lcpr case=end

 */


