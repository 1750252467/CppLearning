/*
 * @lc app=leetcode.cn id=404 lang=cpp
 * @lcpr version=21901
 *
 * [404] 左叶子之和
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
    int sumOfLeftLeaves(TreeNode* root) {
        if(root == NULL) return 0;
        if(root->left == NULL&& root->right == NULL) return 0;
        
        int leftValue = sumOfLeftLeaves(root->left);

        if(root->left&&!root->left->left&&!root->left->right) {
            leftValue = root->left->val;
        }

        int rightValue = sumOfLeftLeaves(root->right);

        int sum = leftValue + rightValue;
        return sum;

    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,9,20,null,null,15,7]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */


