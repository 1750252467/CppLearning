// @lcpr-before-debug-begin




// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=704 lang=cpp
 * @lcpr version=21801
 *
 * [704] 二分查找
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
    int search(vector<int>& nums, int target) {

        int left = 0 ,right = nums.size()-1;
        // 定义target在左闭右闭的区间里，[left, right]
        
        while(left<=right) {// 当left==right，区间[left, right]依然有效，所以用 <=
            int middle = left + (right - left >> 1);
            //还可以写成left + ((right -left)/2)
            // 防止溢出 等同于(left + right)/2
            if(nums[middle]<target)
                left = middle + 1;// target 在右区间，所以[middle + 1, right]
            else if(nums[middle]>target)
                right = middle - 1;// target 在左区间，所以[left, middle - 1]
            else 
                return middle; // 数组中找到目标值，直接返回下标
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
// [-1,0,3,5,9,12]\n9\n
// @lcpr case=end

// @lcpr case=start
// [-1,0,3,5,9,12]\n2\n
// @lcpr case=end

 */


