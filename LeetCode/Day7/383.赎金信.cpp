/*
 * @lc app=leetcode.cn id=383 lang=cpp
 * @lcpr version=21801
 *
 * [383] 赎金信
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
    bool canConstruct(string ransomNote, string magazine) {
        std::unordered_map<char,int> rmap,mmap;
        for(char ch : ransomNote) {
            rmap[ch]++;
        }

        for(char ch : magazine) {
            if(rmap.find(ch)!= rmap.end())
            mmap[ch]++;
        }

        for(auto ch: rmap) {
            if(mmap.find(ch.first)==mmap.end())
                return false;
            if(rmap[ch.first] > mmap[ch.first])
                return false;
        }

        return true;
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
// "a"\n"b"\n
// @lcpr case=end

// @lcpr case=start
// "aa"\n"ab"\n
// @lcpr case=end

// @lcpr case=start
// "aa"\n"aab"\n
// @lcpr case=end

 */


