/*
 * @lc app=leetcode.cn id=24 lang=cpp
 * @lcpr version=21801
 *
 * [24] 两两交换链表中的节点
 */

// @lc code=start

#if 0
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 #endif
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* cur = dummyHead;
        while(cur->next != nullptr && cur->next->next != nullptr) {
            ListNode* tmp = cur->next;
            ListNode* tmp1 = cur->next->next->next;

            cur->next = cur->next->next;
            cur->next->next = tmp;
            cur->next->next->next = tmp1;
            
            cur = cur->next->next;
        }
        return dummyHead->next;
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
// [1,2,3,4]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */


