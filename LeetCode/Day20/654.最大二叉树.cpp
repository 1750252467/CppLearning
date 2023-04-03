/*
 * @lc app=leetcode.cn id=654 lang=cpp
 * @lcpr version=21901
 *
 * [654] 最大二叉树
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

#if 0
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
#endif
class Solution {

private:
    TreeNode* traveral(vector<int>& nums,int left,int right) {
        if(left>=right) return nullptr;

        int maxValueIndex = left;
        for(int i = left + 1; i < right; i++) {
            if(nums[i] > nums[maxValueIndex]) maxValueIndex = i;
        }

        TreeNode* root = new TreeNode(nums[maxValueIndex]);

        root->left = traveral(nums,left,maxValueIndex);

        root->right = traveral(nums,maxValueIndex+1,right);

        return root;
    }


public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return traveral(nums,0,nums.size());
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,2,1,6,0,5]\n
// @lcpr case=end

// @lcpr case=start
// [3,2,1]\n
// @lcpr case=end

 */


