/*
 * @lc app=leetcode.cn id=406 lang=cpp
 * @lcpr version=21906
 *
 * [406] 根据身高重建队列
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
    public:
    static bool cmp(const vector<int>& a,const vector<int>& b) {
        if(a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(),people.end(),cmp);
        list<vector<int>> que;
        for(int i = 0;i < people.size(); ++i) {
            int position = people[i][1];
            list<vector<int>>::iterator it = que.begin();
            while(position--) {
                it++;
            }
            que.insert(it,people[i]);
        }
        return vector<vector<int>>(que.begin(),que.end());
        }
};
// @lc code=end



/*
// @lcpr case=start
// [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]\n
// @lcpr case=end

// @lcpr case=start
// [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]\n
// @lcpr case=end

 */

