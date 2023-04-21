/*
 * @lc app=leetcode.cn id=738 lang=cpp
 * @lcpr version=21906
 *
 * [738] 单调递增的数字
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
    int monotoneIncreasingDigits(int n) {
        string strNum = to_string(n);
        
        int flag = strNum.size();
        for(int i = strNum.size()-1; i> 0;--i) {
            if(strNum[i-1] > strNum[i]){
            flag = i;
            strNum[i-1]--;
            }
        }
          for(int i = flag ;i < strNum.size();i++) {
            strNum[i] = '9';
        }
        return stoi(strNum);
    }

};
// @lc code=end



/*
// @lcpr case=start
// 10\n
// @lcpr case=end

// @lcpr case=start
// 1234\n
// @lcpr case=end

// @lcpr case=start
// 332\n
// @lcpr case=end

 */

