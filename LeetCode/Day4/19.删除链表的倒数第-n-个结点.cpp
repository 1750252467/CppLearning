/*
 * @lc app=leetcode.cn id=19 lang=cpp
 * @lcpr version=21801
 *
 * [19] 删除链表的倒数第 N 个结点
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* slow = dummyHead;
        ListNode* fast = dummyHead;
        while(n--&&fast!=nullptr) {
            fast = fast->next;
        }
         fast = fast->next;
        while(fast){
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;
 #if 0 //释放      
       ListNode* tmp = slow->next;
        slow->next= tmp->next;
        delete tmp;
#endif
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
// [1,2,3,4,5]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n1\n
// @lcpr case=end

 */


