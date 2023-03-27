/*
 * @lc app=leetcode.cn id=347 lang=cpp
 * @lcpr version=21801
 *
 * [347] 前 K 个高频元素
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
    class mycomparison {
    public:
        bool operator()(const pair<int,int>& lhs, const pair<int,int>& rhs) {
            return lhs.second > rhs.second;
        }
    };

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> map;
        for(int i = 0; i < nums.size(); i++) {
            map[nums[i]]++;
        }
        priority_queue<pair<int,int>,vector<pair<int,int>>,mycomparison> pri_que;

        for(unordered_map<int,int>::iterator it = map.begin();it!= map.end();it++) {
            pri_que.push(*it);
            if(pri_que.size()>k) {
                pri_que.pop();
            }
        }

        vector<int> result(k);

        for(int i = k-1; i >= 0; i-- ) {
            result[i] = pri_que.top().first;
            pri_que.pop();
        }

        return result;


    }
};
// @lc code=end

// @lcpr-div-debug-arg-start
// funName=
// paramTypes= []
// returnType=
// @lcpr-div-debug-arg-end


/*
// @lcpr case=start
// [1,1,1,2,2,3]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n
// @lcpr case=end

 */


