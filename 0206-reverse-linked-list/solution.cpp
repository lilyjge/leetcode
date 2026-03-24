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
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* prev = nullptr;
        // cout << "prev " << prev->val << endl;
        // cout << "head " << head->val << endl;
        while(head != nullptr) {
            ListNode* next = head->next;
            // cout << "prev " << prev->val << endl;
            // cout << "head " << head->val << endl;
            // cout << "next " << next << endl;
            head->next = prev;
            prev = head;
            head = next;
        }
        // cout << "ans " << prev->val << endl;
        // cout << prev->next->val << " " << prev->next->next->val << " " << prev->next->next->next->val << endl;
        // cout << prev->next->next->next->next->val << " " <<prev->next->next->next->next->next << endl;
        return prev;
    }
};
