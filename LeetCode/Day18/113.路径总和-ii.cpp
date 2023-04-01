/*
 * @lc app=leetcode.cn id=113 lang=cpp
 * @lcpr version=21901
 *
 * [113] 路径总和 II
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
    vector<vector<int>> result;
    vector<int> path;

    void traversal(TreeNode* cur,int count) {
        if(!cur->left && !cur->right && count==0) {
            result.push_back(path);
            return;
        }
        if(!cur->left&&!cur->right) return;

        if(cur->left) {
            path.push_back(cur->left->val);
            count -=cur->left->val;
            traversal(cur->left,count);
            count += cur->left->val;
            path.pop_back();
        }

        if(cur->right) {
            path.push_back(cur->right->val);
            count -= cur->right->val;
            traversal(cur->right,count);
            count +=cur->right->val;
            path.pop_back();
        }

        return;

    }


    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        result.clear();
        path.clear();
        if(root == NULL) return result;
        path.push_back(root->val);
        traversal(root,targetSum-root->val);
        return result;


    }
};
// @lc code=end



/*
// @lcpr case=start
// [5,4,8,11,null,13,4,7,2,null,null,5,1]\n22\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n5\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n0\n
// @lcpr case=end

 */


