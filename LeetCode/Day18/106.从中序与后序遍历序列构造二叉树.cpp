/*
 * @lc app=leetcode.cn id=106 lang=cpp
 * @lcpr version=21901
 *
 * [106] 从中序与后序遍历序列构造二叉树
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
public:
    TreeNode* traversal (vector<int>& inorder, vector<int>& postorder) {
        if(postorder.size() == 0) return NULL;

        int rootValue = postorder[postorder.size()-1];
        TreeNode* root = new TreeNode(rootValue);

        if(postorder.size() == 1) return root;

        int delimiterIndex;
        for(delimiterIndex = 0; delimiterIndex < inorder.size(); delimiterIndex++) {
            if(inorder[delimiterIndex] == rootValue) break;
        }

        vector<int> leftInorder(inorder.begin(),inorder.begin() + delimiterIndex);

        vector<int> rightInorder(inorder.begin() + delimiterIndex + 1,inorder.end() );

        postorder.resize(postorder.size()-1);

        vector<int> leftPostorder(postorder.begin(),postorder.begin()+leftInorder.size());

        vector<int> rightPostorder(postorder.begin()+leftInorder.size(),postorder.end());

        root->left = traversal(leftInorder,leftPostorder);
        root->right = traversal(rightInorder,rightPostorder);

        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.size() == 0 || postorder.size() == 0) return NULL;
        return traversal(inorder,postorder);
   }
};
// @lc code=end



/*
// @lcpr case=start
// [9,3,15,20,7]\n[9,15,7,20,3]\n
// @lcpr case=end

// @lcpr case=start
// [-1]\n[-1]\n
// @lcpr case=end

 */


