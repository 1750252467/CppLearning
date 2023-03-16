/*
 * @lc app=leetcode.cn id=27 lang=cpp
 * @lcpr version=21801
 *
 * [27] 移除元素
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
//暴力解法
/*class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int size = nums.size();
        for(int i = 0 ;i < size; ++i) {
            if(nums[i] == val) {
                for(int j = i+1; j < size; ++j) {
                    nums[j - 1] = nums[j];
                }
                --i;
                --size;
            }
        }
        return size;
    }
};*/
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
       int slowindex = 0 ;
       for(int fastindex = 0; fastindex <nums.size();++fastindex) {
        if(val != nums[fastindex]) {
            nums[slowindex++] = nums[fastindex];
        }
       }
       return slowindex; 
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
// [3,2,2,3]\n3\n
// @lcpr case=end

// @lcpr case=start
// [0,1,2,2,3,0,4,2]\n2\n
// @lcpr case=end

 */


