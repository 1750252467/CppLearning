// @lcpr-before-debug-begin




// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=203 lang=cpp
 * @lcpr version=21801
 *
 * [203] 移除链表元素
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
/*struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {};
    ListNode(int x) : val(x), next(nullptr) {};
    ListNode(int x, ListNode *next) : val(x), next(next) {};
 };
*/
/*class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* p ,*q;
        p = head,q = head->next;
        while(q){
            if(p->val==val&& p == head){
                 head = q;
            }else if(p->val==val) {
                p = q->next;
            }
            p = p->next;
            q = q->next;
        }
        return head;
    }
};
*/

/*class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
       //删除头结点
       while(head != NULL && head->val == val) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
       }
        //删除非头结点
       ListNode* cur = head;
       while(cur != NULL && cur->next != NULL ) {
            if(cur->next->val == val) {
                ListNode* tmp =cur->next;
                cur->next = cur->next->next;
                delete tmp;
            }else {
                cur = cur->next;
            }
       }
        return head;
    }
};
*/
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* cur = dummyHead;
        while(cur->next != NULL) {
            if(cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;    
                delete tmp;
            }else {
                cur = cur->next;
            }
        } 
        head = dummyHead->next;
        delete dummyHead;
        return head;
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
// [1,2,6,3,4,5,6]\n6\n
// @lcpr case=end

// @lcpr case=start
// []\n1\n
// @lcpr case=end

// @lcpr case=start
// [7,7,7,7]\n7\n
// @lcpr case=end

 */


