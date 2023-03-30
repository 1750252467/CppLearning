/*
 * @lc app=leetcode.cn id=104 lang=cpp
 * @lcpr version=21901
 *
 * [104] 二叉树的最大深度
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
 /*
class Solution {
public:
    int getdepth(TreeNode* node) 
    {
        if(node == NULL) return 0;
        int leftdepth = getdepth(node->left);
        int rightdepth = getdepth(node->right);
        int depth = 1 + max(leftdepth,rightdepth);
        return depth;
     }
    int maxDepth(TreeNode* root) {
        return getdepth(root);
    }
};

*/


class Solution {
public:

    int maxDepth(TreeNode* root) {
        if(root == NULL) return 0;
        int depth = 0;
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()) {
            int size = que.size();
            depth++;
            for(int i = 0;i<size;++i) {
                TreeNode* node = que.front();
                que.pop();
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
             }
        }
        return depth;
    }
};



// @lc code=end




