/*
 * @lc app=leetcode.cn id=面试题 02.07 lang=cpp
 * @lcpr version=21801
 *
 * [面试题 02.07] 链表相交
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

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
 };
#endif
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* curA = headA;
        ListNode* curB = headB;
        int sizeA = 0 , sizeB = 0;
        //链表A的长度
           while(curA) {
            curA =  curA->next;
            sizeA++;
        }
        // 求链表B的长度
       while(curB) {
            curB = curB->next;
            sizeB++;
       }
       curA = headA;
       curB = headB;       
        // 让curA为最长链表的头，lenA为其长度
      if(sizeB > sizeA) {
        swap(sizeA,sizeB);
        swap(curA,curB);
      }
        // 求长度差
        int grp = sizeA - sizeB;

        // 让curA和curB在同一起点上（末尾位置对齐）
      while(grp--){
        curA = curA->next; 
      }

    // 遍历curA 和 curB，遇到相同则直接返回
    while(curA != nullptr) {
        if(curA == curB){
            return curA;
        }
        curA = curA->next;
        curB = curB->next;
    }
    return NULL;
    }
};
// @lc code=end

// @lcpr-div-debug-arg-start
// funName=
// paramTypes= []
// returnType=
// @lcpr-div-debug-arg-end


/*
// @lcpr case=start
// 8\n[4,1,8,4,5]\n[5,0,1,8,4,5]\n2\n3\n
// @lcpr case=end

// @lcpr case=start
// 2\n[0,9,1,2,4]\n[3,2,4]\n3\n1\n
// @lcpr case=end

// @lcpr case=start
// 0\n[2,6,4]\n[1,5]\n3\n2\n
// @lcpr case=end

 */


