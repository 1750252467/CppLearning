/*
 * @lc app=leetcode.cn id=513 lang=cpp
 * @lcpr version=21901
 *
 * [513] 找树左下角的值
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
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> que;
        if(root != NULL) que.push(root);
        int result = 0;
        while(!que.empty()) {
            int size = que.size();
            for(int i = 0;i < size; ++i ) {
                TreeNode* node = que.front();
                que.pop();
                if(i == 0) result = node->val;
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);            
            }
        }
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,1,3]\n
// @lcpr case=end

// @lcpr case=start
// 
// @lcpr case=end

 */


