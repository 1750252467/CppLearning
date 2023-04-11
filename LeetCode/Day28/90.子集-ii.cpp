/*
 * @lc app=leetcode.cn id=90 lang=cpp
 * @lcpr version=21902
 *
 * [90] 子集 II
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
    void backtracking(vector<int>& nums,int startIndex, vector<bool>& used) {
        result.push_back(path);
        for(int i = startIndex; i < nums.size(); ++i) {

            if(i > 0 && nums[i] == nums[i-1] && used[i-1] == false) {
                continue;
            }

            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums,i + 1,used);
            used[i] = false;
            path.pop_back();
        }

    }
 public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        result.clear();
        path.clear();
        vector<bool> used(nums.size(),false);
        sort(nums.begin(),nums.end());
        backtracking(nums,0,used);
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,2]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n
// @lcpr case=end

 */


