/*
 * @lc app=leetcode.cn id=20 lang=cpp
 * @lcpr version=21801
 *
 * [20] 有效的括号
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
#if 0
class Solution {
public:
    bool isValid(string s) {
        if(s.size()%2!=0) return false;
        stack<char> st;
        for(int i = 0; i<s.size();++i) {
            if(s[i] == '{') st.push('}');
            else if(s[i]=='[') st.push(']');
            else if(s[i]=='(') st.push(')');
            else if(st.empty() || st.top() !=s[i]) return false;
            else st.pop();
        }
        return st.empty();
     }
};
#endif

class Solution {
public:
    string removeDuplicates(string s) {
        string result;
        for(char ch : s) {
            if(result.empty() || result.back() != ch) {
                result.push_back(ch);
            }
            else {
                result.pop_back();
            }
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
// "()"\n
// @lcpr case=end

// @lcpr case=start
// "()[]{}"\n
// @lcpr case=end

// @lcpr case=start
// "(]"\n
// @lcpr case=end

 */


