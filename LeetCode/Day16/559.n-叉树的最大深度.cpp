/*
 * @lc app=leetcode.cn id=559 lang=cpp
 * @lcpr version=21901
 *
 * [559] N 叉树的最大深度
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
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
#endif

class Solution {
public:
    int getdepth(Node* node) {
        if(node == NULL ) return 0;
        int depth = 0;
        for(int i = 0; i < node->children.size();++i ) {
            depth = max(depth,getdepth(node->children[i]));
        }
        return depth+1;
    }
    int maxDepth(Node* root) {
        return getdepth(root);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,null,3,2,4,null,5,6]\n
// @lcpr case=end

// @lcpr case=start
// [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]\n
// @lcpr case=end

 */


