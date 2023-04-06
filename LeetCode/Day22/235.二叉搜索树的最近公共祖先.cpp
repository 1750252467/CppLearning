/*
 * @lc app=leetcode.cn id=235 lang=cpp
 * @lcpr version=21901
 *
 * [235] 二叉搜索树的最近公共祖先
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
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
#endif

class Solution {

private:
    TreeNode* traversal(TreeNode* cur, TreeNode* p, TreeNode* q) {
        if(cur == NULL) return cur;
                                                    // 中
        if(cur->val > p->val && cur->val > q->val) {// 左
            TreeNode*  left = traversal(cur->left,p,q);
            if(left != NULL) {
                return left;
            }
        }

        if(cur->val < p->val && cur->val < q->val) {// 右
            TreeNode* right = traversal(cur->right,p,q);
            if(right != NULL) {
                return right;
            }
        }
        return cur;
     }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return traversal(root,p,q);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [6,2,8,0,4,7,9,null,null,3,5]\n2\n8\n
// @lcpr case=end

// @lcpr case=start
// [6,2,8,0,4,7,9,null,null,3,5]\n2\n4\n
// @lcpr case=end

 */


