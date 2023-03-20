/*
 * @lc app=leetcode.cn id=242 lang=cpp
 * @lcpr version=21801
 *
 * [242] 有效的字母异位词
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
    bool isAnagram(string s, string t) {
        std::unordered_map<char,int> ss,tt;
        for(char ch: s)
            ++ss[ch];
        for(char ch : t)
            ++tt[ch];
        bool flag = true;
        if(ss.size()!=tt.size())
            flag = false;        
        for(auto ch: ss) {
            if(ch.second!=tt[ch.first])
                flag = false;
        }

        return flag;
        
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
// "anagram"\n"nagaram"\n
// @lcpr case=end

// @lcpr case=start
// "rat"\n"car"\n
// @lcpr case=end

 */


