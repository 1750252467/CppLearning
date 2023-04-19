/*
 * @lc app=leetcode.cn id=452 lang=cpp
 * @lcpr version=21906
 *
 * [452] 用最少数量的箭引爆气球
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
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.size() == 0) return 0;
        sort(points.begin(),points.end(),cmp);

        int result = 1;
        for(int i = 1; i < points.size();++i) {
            if(points[i][0] > points[i-1][1]) {
                result++;
            }
            else {
                points[i][1] = min(points[i-1][1],points[i][1]);
            }
        }
        return  result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[10,16],[2,8],[1,6],[7,12]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[3,4],[5,6],[7,8]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[2,3],[3,4],[4,5]]\n
// @lcpr case=end

 */

