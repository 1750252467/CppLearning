/*
 * @lc app=leetcode.cn id=108 lang=cpp
 * @lcpr version=21901
 *
 * [108] 将有序数组转换为二叉搜索树
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
    TreeNode* traversal(vector<int>& nums, int left, int right) {
        if(left > right) return nullptr;
        int mid = left +((right-left)/2);
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = traversal(nums,left,mid - 1);
        root->right = traversal(nums,mid+1,right);
        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
       TreeNode* root = traversal(nums,0,nums.size()-1); 
       return root;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [-10,-3,0,5,9]\n
// @lcpr case=end

// @lcpr case=start
// [1,3]\n
// @lcpr case=end

 */


