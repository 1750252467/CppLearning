/*
 * @lc app=leetcode.cn id=剑指 Offer 05 lang=cpp
 * @lcpr version=21801
 *
 * [剑指 Offer 05] 替换空格
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
    string replaceSpace(string s) {
        string ss;
        for(char ch :s){
            if(ch==' ') {
                ss+="%20";
            }else {
                ss+=ch;
            }

        }
        return ss;
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
// "We are happy."\n
// @lcpr case=end

 */


