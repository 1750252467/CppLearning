/*
 * @lc app=leetcode.cn id=222 lang=cpp
 * @lcpr version=21901
 *
 * [222] 完全二叉树的节点个数
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
    int getNodesNum(TreeNode* cur) {
        if(cur == NULL) return 0;
        int leftNum = getNodesNum(cur->left);
        int rightNum = getNodesNum(cur->right);
        int treeNum = leftNum + rightNum +1;
        return treeNum;
    }

    int countNodes(TreeNode* root) {
        return getNodesNum(root);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5,6]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */


