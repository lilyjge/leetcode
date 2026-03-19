/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* fake = new ListNode(-200);
        ListNode* head = fake;
        while(list2 != nullptr && list1 != nullptr) {
            if (list1->val < list2->val) {
                fake->next = list1;
                list1 = list1->next;
            } else {
                fake->next = list2;
                list2 = list2->next;
            }
            fake = fake->next;
        }
        if(list1 != nullptr) {
            fake->next = list1;
        }
        else if(list2 != nullptr) {
            fake->next = list2;
        }
        return head->next;
    }
};
