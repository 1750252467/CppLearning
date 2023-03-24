/*
 * @lc app=leetcode.cn id=28 lang=cpp
 * @lcpr version=21801
 *
 * [28] 找出字符串中第一个匹配项的下标
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
/*
class Solution {
public:
    int strStr(string haystack, string needle) {
        int i=0,j=0;
        int start = 0;
        if(needle.size()>haystack.size()) {
            return -1;
        }
        if(needle.size()==haystack.size()) {
                if(haystack.compare(0,haystack.size()-1,needle,0,needle.size()-1))
                    return 0;
        }
        while(i<haystack.size()&&j<needle.size()) {
            if(haystack[i]!=needle[j]) {
                i++;
            }else {
                start = i;
                while(i<haystack.size()&&j<needle.size()){
                    i++;
                    j++;
                    if(haystack[i]!=needle[j]) break;
                    else if(j==needle.size()-1){
                        return start;
                    }
                }

            }
        }
        return -1;
    }
};

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        for (int i = 0; i + m <= n; i++) {
            bool flag = true;
            for (int j = 0; j < m; j++) {
                if (haystack[i + j] != needle[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return i;
            }
        }
        return -1;
    }
};

*/

class Solution {
public:
    void getNext(int* next, const string&  s) {
        int j = 0;
        next[0] = 0;
        for(int i = 1;i < s.size(); ++i) {
            while(j > 0 && s[i] !=  s[j]) {
                j = next[j-1]; 
            }
            if(s[i] == s[j]) {
                ++j;
            }
            next[i] = j;
        }
    }
    int strStr(string haystack, string needle) {
        if(needle.size() == 0) {
            return 0;
        }
        int next[needle.size()];
        getNext(next,needle);
        int j = 0;
        for(int i = 0; i < haystack.size(); ++i ) {
            while(j > 0 && haystack[i] != needle[j]) {
                j = next[j-1];
            }
            if(haystack[i] == needle[j]) {
                ++j;
            }
            if(j == needle.size() ) {
                return (i - needle.size() +1);
            }
        }
        return -1;
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
// "sadbutsad"\n"sad"\n
// @lcpr case=end

// @lcpr case=start
// "leetcode"\n"leeto"\n
// @lcpr case=end

 */


