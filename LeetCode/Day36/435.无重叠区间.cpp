/*
 * @lc app=leetcode.cn id=435 lang=cpp
 * @lcpr version=21906
 *
 * [435] 无重叠区间
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
    static bool cmp(const vector<int>& a,const vector<int>& b) {
        return a[0] < b[0];       
    }
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if(intervals.size() == 0) return 0;
        sort(intervals.begin(),intervals.end(),cmp);
        int count = 0;
        int end =intervals[0][1];
        for(int i = 1; i < intervals.size(); ++i) {
            if(intervals[i][0] >= end) end = intervals[i][1];
            else {
                end = min(end,intervals[i][1]);
                ++count;
            }
        } 
        return count;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2],[2,3],[3,4],[1,3]]\n
// @lcpr case=end

// @lcpr case=start
// [ [1,2], [1,2], [1,2] ]\n
// @lcpr case=end

// @lcpr case=start
// [ [1,2], [2,3] ]\n
// @lcpr case=end

 */

