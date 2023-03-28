// @lcpr-before-debug-begin




// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=239 lang=cpp
 * @lcpr version=21801
 *
 * [239] 滑动窗口最大值
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
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        if(k==nums.size()) {
            sort(nums.begin(),nums.end());
            return {nums[nums.size()-1]};
        }

        for(int i = 0; i <nums.size()-k+1; ++i) {
            int max = INT32_MIN;
            for(int j = i ;j <= i+k-1; ++j) {
                if(nums[j] > max) {
                    max = nums[j];
                }
            }
             result.push_back(max);
        }
        return result;
    }
};

#endif

class Solution {
private:
    class MyQueue {
    public:
        deque<int> que;

        void pop(int value) {
            if(!que.empty() && value == que.front()) {
                que.pop_front();
            }
        }

        void push(int value) {
            while(!que.empty() && value>que.back()) {
                que.pop_back();
            }
            que.push_back(value);
        }

        int front() {
            return que.front();
        }



    };
public:
    vector<int> maxSlidingWindow(vector<int>& nums,int k) {
        MyQueue que;
        vector<int> result;
        for(int i = 0; i < k; ++i) {
            que.push(nums[i]);
        }

        result.push_back(que.front());

        for(int i = k; i < nums.size(); ++i) {
            que.pop(nums[i-k]);
            que.push(nums[i]);
            result.push_back(que.front());
        }

        return result;
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
// [1,3,-1,-3,5,3,6,7]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n
// @lcpr case=end

 */


