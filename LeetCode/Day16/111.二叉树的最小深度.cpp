/*
 * @lc app=leetcode.cn id=111 lang=cpp
 * @lcpr version=21901
 *
 * [111] 二叉树的最小深度
 */

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
public:
    int minDepth(TreeNode* root) {
        if(root == nullptr ) return 0;
        if(root->left == nullptr && root->right!= nullptr) {
            return 1+minDepth(root->right);
        }
        if(root->left != nullptr && root->right == nullptr) {
            return 1+minDepth(root->left);
        }
        return 1 + min(minDepth(root->left),minDepth(root->right));
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,9,20,null,null,15,7]\n
// @lcpr case=end

// @lcpr case=start
// [2,null,3,null,4,null,5,null,6]\n
// @lcpr case=end

 */


