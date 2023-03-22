// @lcpr-before-debug-begin




// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=541 lang=cpp
 * @lcpr version=21801
 *
 * [541] 反转字符串 II
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

    void reverseString(string& s) {
        int left = 0,right = s.size()-1;
        while(left <= right) {
            swap(s[left],s[right]);
            left++;
            right--;
        }
    }

    string reverseStr(string s, int k) {
        int index = 0;
        string result = {};
        while(index < s.size()) {
            if(s.size() > 2*k) { 
            string res1 = s.substr(index,k);
            reverseString(res1);
            result+=res1;
            }
            string res2;
            if(s.size()-1-index <k) {
                res2 = s.substr(index,s.size()-1-index); 
                reverseString(res2);
                result += res2;

            }else if(s.size()-1-index < 2*k&&s.size()-1-index >= k){
                res2 = s.substr(index,k);
                result += res2;
            }else
             index += 2*k;
        }
        return result;
    }
};
#endif

class Solution {
public:
    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += (2 * k)) {
            // 1. 每隔 2k 个字符的前 k 个字符进行反转
            // 2. 剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符
            if (i + k <= s.size()) {
                reverse(s.begin() + i, s.begin() + i + k );
            } else {
                // 3. 剩余字符少于 k 个，则将剩余字符全部反转。
                reverse(s.begin() + i, s.end());
            }
        }
        return s;
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
// "abcd"\n2\n
// @lcpr case=end

 */


