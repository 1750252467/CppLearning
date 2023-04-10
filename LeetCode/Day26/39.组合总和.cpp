/*
 * @lc app=leetcode.cn id=39 lang=cpp
 * @lcpr version=21902
 *
 * [39] 组合总和
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
    void backtracking(vector<int>& canditates,int target,int sum,int startIndex) {
        if(sum == target) {
            result.push_back(path);
            return;
        }

        for(int i = startIndex; i <canditates.size() && sum + canditates[i] <= target; ++i) {
            sum += canditates[i];
            path.push_back(canditates[i]);
            backtracking(canditates,target,sum,i);
            sum -= canditates[i];
            path.pop_back();
        }


    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        result.clear();
        path.clear();
        sort(candidates.begin(),candidates.end());
        backtracking(candidates,target,0,0);
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,6,7]\n7\n
// @lcpr case=end

// @lcpr case=start
// [2,3,5]\n8\n
// @lcpr case=end

// @lcpr case=start
// [2]\n1\n
// @lcpr case=end

 */


