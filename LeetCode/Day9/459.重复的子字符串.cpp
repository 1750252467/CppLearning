/*
 * @lc app=leetcode.cn id=459 lang=cpp
 * @lcpr version=21801
 *
 * [459] 重复的子字符串
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
    bool repeatedSubstringPattern(string s) {
        string t = s + s;
        t.erase(t.begin());t.erase(t.end()-1);
        if(t.find(s) != std::string::npos ) return true;
        return false;
    }
};

#endif

class Solution
{
public:
    void getNext(int* next,const string& s) {
        next[0] = 0;
        int j = 0;
        for(int i = 1; i < s.size(); ++i) {
            while(j > 0 && s[i] !=s[j] ) {
                j = next[j-1];
            }
            if(s[i] == s[j]) {
                j++;
            }
            next[i] = j;
        }
    }

    bool repeatedSubstringPattern(string s) {
        if(s.size() == 0) {
            return false;
        }
        int next[s.size()];
        getNext(next,s);
        int len = s.size();

        if(next[len - 1] != 0 && len % (len - (next[len-1])) == 0) {
            return true;
        }
        return false;

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
// "abab"\n
// @lcpr case=end

// @lcpr case=start
// "aba"\n
// @lcpr case=end

// @lcpr case=start
// "abcabcabcabc"\n
// @lcpr case=end

 */


