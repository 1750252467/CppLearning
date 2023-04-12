/*
 * @lc app=leetcode.cn id=47 lang=cpp
 * @lcpr version=21905
 *
 * [47] 全排列 II
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
    void backtarcking(vector<int>& nums, vector<bool>& used) {

        if(path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        for(int i = 0; i < nums.size(); ++i) {
            if(i > 0 && nums[i] == nums[i-1] && used[i-1] == false) {
                continue;
            }
            
            if(used[i] == false) {
                used[i] = true;
                path.push_back(nums[i]);
                backtarcking(nums,used);
                path.pop_back();
                used[i] = false;
            }
        }
    } 
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        result.clear();
        path.clear();
        sort(nums.begin(),nums.end());
        vector<bool> used(nums.size(),false);
        backtarcking(nums,used);
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

 */


