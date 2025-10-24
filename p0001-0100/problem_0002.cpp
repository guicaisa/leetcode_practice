#include "stdio.h"

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution 
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode* dummy = new ListNode();
        ListNode* head = dummy;
        int carry = 0;
        while (l1 || l2)
        {
            int temp = carry;
            if (l1) 
            {
                temp += l1->val;
                l1 = l1->next;
            }
            if (l2)
            {
                temp += l2->val;
                l2 = l2->next;
            }
            
            int num = temp % 10;
            carry = temp / 10;

            head->next = new ListNode(num);
            head = head->next;
        }
        
        if (carry)
        {
            head->next = new ListNode(carry);
        }

        return dummy->next;
    }
};

int main(int argc, char** argv)
{
    Solution s;

    ListNode* n1_1_1 = new ListNode(2);
    ListNode* n1_1_2 = new ListNode(4);
    ListNode* n1_1_3 = new ListNode(3);
    n1_1_1->next = n1_1_2;
    n1_1_2->next = n1_1_3;
    ListNode* n1_2_1 = new ListNode(5);
    ListNode* n1_2_2 = new ListNode(6);
    ListNode* n1_2_3 = new ListNode(4);
    n1_2_1->next = n1_2_2;
    n1_2_2->next = n1_2_3;
    ListNode* result = s.addTwoNumbers(n1_1_1, n1_2_1);
    

    return 0;
}