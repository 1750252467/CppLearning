/*
 * @lc app=leetcode.cn id=491 lang=cpp
 * @lcpr version=21902
 *
 * [491] 递增子序列
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
    void backtracking(vector<int>& nums, int startIndex) {
        if(path.size() > 1) {
            result.push_back(path);
        }
        int used[201] = {0};
        for(int i = startIndex; i < nums.size(); ++i) {
            if((!path.empty() && nums[i] < path.back())||
                used[nums[i]+100] == 1) {
                    continue;
            }
            used[nums[i] + 100] = 1;
            path.push_back(nums[i]);
            backtracking(nums,i+1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {   
        result.clear();
        path.clear();
        backtracking(nums,0);
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,6,7,7]\n
// @lcpr case=end

// @lcpr case=start
// [4,4,3,2,1]\n
// @lcpr case=end

 */


