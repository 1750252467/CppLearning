/*
 * @lc app=leetcode.cn id=1047 lang=cpp
 * @lcpr version=21801
 *
 * [1047] 删除字符串中的所有相邻重复项
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
    string removeDuplicates(string s) {
        stack<char> st;
        string result="";
        for(char ch:s){
            if(st.empty()||ch !=st.top()) st.push(ch);
            else st.pop();    
        }

        while(!st.empty()) {
            result+=st.top();
            st.pop();
        }
        reverse(result.begin(),result.end());
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
// 
// @lcpr case=end

 */


