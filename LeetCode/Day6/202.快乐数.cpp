/*
 * @lc app=leetcode.cn id=202 lang=cpp
 * @lcpr version=21801
 *
 * [202] 快乐数
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
    int getsum(int n) 
    {   
        int sum = 0;
        while(n) {
            sum += (n%10) * (n%10);
            n/=10;
        }
        return sum;

    }
    bool isHappy(int n) {
        unordered_set<int> set;
        while(1) {
            int sum = getsum(n);
            if(sum == 1) 
            {
                return true;
            }

            if(set.find(sum) != set.end()) {
                return false;
            }else {
                set.insert(sum);
            }
            n = sum;



        }
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
// 19\n
// @lcpr case=end

// @lcpr case=start
// 2\n
// @lcpr case=end

 */


