/*
 * @lc app=leetcode.cn id=101 lang=cpp
 * @lcpr version=21901
 *
 * [101] 对称二叉树
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
    bool compare(TreeNode* left,TreeNode* right) {
        if(left == NULL&& right != NULL) return false;
        else if(left != NULL&& right == NULL) return false;
        else if(left == NULL&& right == NULL) return true;
        else if(left->val != right->val) return false;

        bool outside = compare(left->left,right->right);
        bool inside = compare(left->right,right->left);
        bool isSame = outside && inside;

        return isSame;   
    }
    bool isSymmetric(TreeNode* root) {
        if(root == NULL) return true;
        return compare(root->left,root->right);

    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,2,3,4,4,3]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,2,null,3,null,3]\n
// @lcpr case=end

 */


