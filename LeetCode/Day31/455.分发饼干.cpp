/*
 * @lc app=leetcode.cn id=455 lang=cpp
 * @lcpr version=21906
 *
 * [455] 分发饼干
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
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(),g.end());
        sort(s.begin(),s.end());
        int index = s.size()-1;
        int result = 0;
        for(int i = g.size()-1; i >=0; i--) {
            if(index >= 0 && s[index] >= g[i]) {
                result++;
                index--;
            }
        }   
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3]\n[1,1]\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n[1,2,3]\n
// @lcpr case=end

 */

