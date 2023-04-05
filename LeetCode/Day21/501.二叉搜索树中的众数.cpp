/*
 * @lc app=leetcode.cn id=501 lang=cpp
 * @lcpr version=21901
 *
 * [501] 二叉搜索树中的众数
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

private:
    void searchBST(TreeNode* cur, unordered_map<int,int>& map) {
        if(cur == NULL) return;
        map[cur->val]++;
        searchBST(cur->left,map);
        searchBST(cur->right,map);
        return;
    }

    bool static cmp(const pair<int,int>& a,const pair<int,int>& b) {
        return a.second > b.second;

    }
public:
    vector<int> findMode(TreeNode* root) {
        unordered_map<int,int> map;
        vector<int> result;
        if(root == NULL) return result;
        searchBST(root,map);
        vector<pair<int,int>> vec(map.begin(),map.end());
        sort(vec.begin(),vec.end(),cmp);
        result.push_back(vec[0].first);
        for(int i = 1; i < vec.size();i++ ) {

            if(vec[i].second == vec[0].second) result.push_back(vec[i].first);
            else break;
        } 
        return result; 
    };
};
// @lc code=end



/*
// @lcpr case=start
// [1,null,2,2]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n
// @lcpr case=end

 */


