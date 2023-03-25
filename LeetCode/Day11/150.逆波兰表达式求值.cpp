/*
 * @lc app=leetcode.cn id=150 lang=cpp
 * @lcpr version=21801
 *
 * [150] 逆波兰表达式求值
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
    int evalRPN(vector<string>& tokens) {
        stack<long long> st;
        for(int i = 0; i < tokens.size();++i ) {
            if(tokens[i] == "+" ||tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
                long long num1 = st.top();
                st.pop();
                long long num2 = st.top();
                st.pop();
                if(tokens[i] == "+") st.push(num2 + num1);
                if(tokens[i] == "-") st.push(num2 - num1);
                if(tokens[i] == "*") st.push(num2 * num1);
                if(tokens[i] == "/") st.push(num2 / num1);
            }else {
                st.push(stoll(tokens[i]));
            }
        }
        
        int result = st.top();
        st.pop();
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
// ["2","1","+","3","*"]\n
// @lcpr case=end

// @lcpr case=start
// ["4","13","5","/","+"]\n
// @lcpr case=end

// @lcpr case=start
// ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]\n
// @lcpr case=end

 */


