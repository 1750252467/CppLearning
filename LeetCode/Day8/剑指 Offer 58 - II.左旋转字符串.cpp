/*
 * @lc app=leetcode.cn id=剑指 Offer 58 - II lang=cpp
 * @lcpr version=21801
 *
 * [剑指 Offer 58 - II] 左旋转字符串
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
    string reverseLeftWords(string s, int n) {
        string result;
        result += s.substr(n,s.size()-n);
        result += s.substr(0,n); 
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
// "abcdefg"\n2\n
// @lcpr case=end

// @lcpr case=start
// "lrloseumgh"\n6\n
// @lcpr case=end

 */


