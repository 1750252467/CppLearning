/*
 * @lc app=leetcode.cn id=56 lang=cpp
 * @lcpr version=21906
 *
 * [56] 合并区间
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
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        if(intervals.size() == 0) return result;
        sort(intervals.begin(),intervals.end(),[](const vector<int>& a,const vector<int>& b){return a[0] < b[0];});
        result.push_back(intervals[0]);

        for(int i = 1; i < intervals.size(); ++i) {
            if(result.back()[1] >=intervals[i][0]) {
                result.back()[1] = max(result.back()[1],intervals[i][1]);

            }
            else {
                result.push_back(intervals[i]);
            }
        }
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,3],[2,6],[8,10],[15,18]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,4],[4,5]]\n
// @lcpr case=end

 */

