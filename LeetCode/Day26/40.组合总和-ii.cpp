/*
 * @lc app=leetcode.cn id=40 lang=cpp
 * @lcpr version=21902
 *
 * [40] 组合总和 II
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
    void backtracking(vector<int>& candidates,int target,int sum,int startIndex,vector<bool> used) {
        if(sum == target) {
            result.push_back(path);
            return;
        }

        for(int i = startIndex; i < candidates.size() && sum +candidates[i] <= target; ++i) {

            if(i > 0 && candidates[i] == candidates[i-1] && used[i-1] == false ) {
                continue;
            }

            sum += candidates[i];
            path.push_back(candidates[i]);
            used[i] = true;
            backtracking(candidates,target,sum,i+1,used);
            used[i] = false;
            sum -= candidates[i];
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<bool> used(candidates.size(),false);
        path.clear();
        result.clear();
        sort(candidates.begin(),candidates.end());
        backtracking(candidates,target,0,0,used);
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [10,1,2,7,6,1,5]\n8,\n
// @lcpr case=end

// @lcpr case=start
// [2,5,2,1,2]\n5,\n
// @lcpr case=end

 */


