/*
 * @lc app=leetcode.cn id=112 lang=cpp
 * @lcpr version=21901
 *
 * [112] 路径总和
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
    bool traversal(TreeNode* cur, int count) {
        if(!cur->left && !cur->right && count == 0) return true;
        if(!cur->left && !cur->right) return false;

        if(cur->left) {
            count -= cur->left->val;
            if(traversal(cur->left,count)) return true;
            count += cur->left->val;
        }
        
        if(cur->right) {
            count -= cur->right->val;
            if(traversal(cur->right,count)) return true;
            count += cur->right->val;
        }
        return false;

    }
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root==NULL) return false;
        return traversal(root,targetSum-root->val);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [5,4,8,11,null,13,4,7,2,null,null,null,1]\n22\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n5\n
// @lcpr case=end

// @lcpr case=start
// []\n0\n
// @lcpr case=end

 */


