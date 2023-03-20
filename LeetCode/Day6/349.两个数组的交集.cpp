/*
 * @lc app=leetcode.cn id=349 lang=cpp
 * @lcpr version=21801
 *
 * [349] 两个数组的交集
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
    vector<int>intersection(vector<int>& nums1, vector<int>& nums2) {
        std::unordered_set<int> result;
        std::unordered_set<int> nums_get(nums1.begin(),nums1.end());  
        for(int num : nums2 ) {
            if(nums_get.find(num) != nums_get.end()) {
                result.insert(num);
            }
        }
        return vector<int>(result.begin(),result.end());
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
// [1,2,2,1]\n[2,2]\n
// @lcpr case=end

// @lcpr case=start
// [4,9,5]\n[9,4,9,8,4]\n
// @lcpr case=end

 */


