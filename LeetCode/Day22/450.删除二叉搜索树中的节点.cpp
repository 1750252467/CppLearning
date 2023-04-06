/*
 * @lc app=leetcode.cn id=450 lang=cpp
 * @lcpr version=21901
 *
 * [450] 删除二叉搜索树中的节点
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == nullptr) return  root;
        
            if(root->val == key) {
            if(root->left == nullptr && root->right == nullptr ) {
                delete root;
                return nullptr;
            }
            else if(root->left == nullptr) {
                auto reNode = root->right;
                delete root;
                return reNode;
            }

            else if(root->right == nullptr) {
                auto retNode = root->left;

                delete root;
                return retNode;
            }

            else {
                TreeNode* cur = root->right;
                while(cur->left != nullptr) {
                    cur = cur->left;
                }

                cur->left = root->left;
                TreeNode* tmp = root;
                root = root->right;
                delete tmp;
                return root;
            }
        }
    if(root->val > key) root->left = deleteNode(root->left,key);
    if(root->val < key ) root->right = deleteNode(root->right,key);
    return root;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [5,3,6,2,4,null,7]\n3\n
// @lcpr case=end

// @lcpr case=start
// [5,3,6,2,4,null,7]\n0\n
// @lcpr case=end

// @lcpr case=start
// []\n0\n
// @lcpr case=end

 */


