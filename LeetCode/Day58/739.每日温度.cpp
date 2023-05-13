/*
 * @lc app=leetcode.cn id=739 lang=cpp
 * @lcpr version=21907
 *
 * [739] 每日温度
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
    vector<int> dailyTemperatures(vector<int>& temperatures) {
       stack<int> st;
       vector<int> result(temperatures.size(),0);
       st.push(0);
       for(int i = 0; i < temperatures.size(); i++){
        if(temperatures[i] < temperatures[st.top()]) {
            st.push(i);
        }else if(temperatures[i] == temperatures[st.top()]) {
            st.push(i);
        }else {
            while(!st.empty() && temperatures[i] > temperatures[st.top()]) {
                result[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
       }
       return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [73,74,75,71,69,72,76,73]\n
// @lcpr case=end

// @lcpr case=start
// [30,40,50,60]\n
// @lcpr case=end

// @lcpr case=start
// [30,60,90]\n
// @lcpr case=end

 */

