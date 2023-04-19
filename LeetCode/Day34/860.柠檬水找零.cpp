/*
 * @lc app=leetcode.cn id=860 lang=cpp
 * @lcpr version=21906
 *
 * [860] 柠檬水找零
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
    bool lemonadeChange(vector<int>& bills) {
        int five = 0,ten = 0;
        for(int i = 0;i < bills.size();i++) {
            if(bills[i] == 5) {
                ++five;
            }
            else if(bills[i] == 10){
                ++ten;
                --five;
            }else {
                if(ten==0){
                    five-=3;
                }else{
                --ten;
                --five;
                }
            }
            if(five < 0 || ten < 0) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [5,5,5,10,20]\n
// @lcpr case=end

// @lcpr case=start
// [5,5,10,10,20]\n
// @lcpr case=end

 */

