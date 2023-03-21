/*
 * @lc app=leetcode.cn id=454 lang=cpp
 * @lcpr version=21801
 *
 * [454] 四数相加 II
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
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        std::unordered_map<int,int> map;//key:a+b的数值，value:a+b数值出现的次数
        //统计两个数组元素之和，和出现的次数，放到map中
        for(int a : nums1){
            for(int b : nums2) {
                map[a+b]++;
            }
        } 

        int count = 0;// 统计a+b+c+d = 0 出现的次数
        //找到如果 0-(c+d) 在map中出现过的话，就把map中key对应的value也就是出现次数统计出来。
        for(int c : nums3) {
            for(int d : nums4) {
                if(map.find(0-(c+d)) != map.end()) {
                    count += map[0-(c+d)];
                 }
            }
        }
        return count;
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
// [1,2]\n[-2,-1]\n[-1,2]\n[0,2]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n[0]\n[0]\n[0]\n
// @lcpr case=end

 */


