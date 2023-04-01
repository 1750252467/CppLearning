/*
 * @lc app=leetcode.cn id=257 lang=cpp
 * @lcpr version=21901
 *
 * [257] 二叉树的所有路径
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
    void traversal(TreeNode* cur, vector<int>& path, vector<string>& result) {
        path.push_back(cur->val);

        if(cur->left == NULL && cur->right == NULL) {
            string sPath;
            for(int i = 0; i < path.size()-1; ++i) {
                sPath += to_string(path[i]);
                sPath += "->";
            }
            sPath += to_string(path[path.size()-1]);
            result.push_back(sPath);
            return;
        }
        
        if(cur->left) {
            traversal(cur->left,path,result);
            path.pop_back();
        }

        if(cur->right) {
            traversal(cur->right,path,result);
            path.pop_back();
        }


    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        vector<int> path;
        if(root == NULL) return result;
        traversal(root,path,result);
        return result;
        
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,null,5]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */


