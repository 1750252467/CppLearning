/*
 * @lc app=leetcode.cn id=968 lang=cpp
 * @lcpr version=21906
 *
 * [968] 监控二叉树
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
    int result;
    int traversal(TreeNode* cur) {
        if(cur == NULL) return 2;

        int left = traversal(cur->left);
        int right = traversal(cur->right);

        if(left == 2 && right == 2) return 0;

        if(left == 0 || right == 0) {
            result++;
            return 1;
        }

        if(left == 1 || right == 1) return 2;

        return -1;
    }
public:
    int minCameraCover(TreeNode* root) {
        result = 0;
        if(traversal(root) == 0) {
            result++;
        }
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [0,0,null,0,0]\n
// @lcpr case=end

// @lcpr case=start
// [0,0,null,0,null,0,null,null,0]\n
// @lcpr case=end

 */

