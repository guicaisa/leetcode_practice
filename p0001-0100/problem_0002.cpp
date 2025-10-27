#include "stdio.h"

// https://leetcode.cn/problems/add-two-numbers/

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
    //1. 遍历
    //同时遍历2个链表，相加其数值并生成新的节点添加到结果链表后面
    //需要注意的是保留加法的进位值，以及遍历结束后如果进位置非0需要再额外添加一个节点 
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

// int main(int argc, char** argv)
// {
//     Solution s;

//     ListNode* n1_1_1 = new ListNode(2);
//     ListNode* n1_1_2 = new ListNode(4);
//     ListNode* n1_1_3 = new ListNode(3);
//     n1_1_1->next = n1_1_2;
//     n1_1_2->next = n1_1_3;
//     ListNode* n1_2_1 = new ListNode(5);
//     ListNode* n1_2_2 = new ListNode(6);
//     ListNode* n1_2_3 = new ListNode(4);
//     n1_2_1->next = n1_2_2;
//     n1_2_2->next = n1_2_3;
//     ListNode* result = s.addTwoNumbers(n1_1_1, n1_2_1);
    
//     ListNode* n2_1_1 = new ListNode(0);
//     ListNode* n2_2_1 = new ListNode(0);
//     result = s.addTwoNumbers(n2_1_1, n2_2_1);

//     ListNode* n3_1_1 = new ListNode(9);
//     ListNode* n3_1_2 = new ListNode(9);
//     ListNode* n3_1_3 = new ListNode(9);
//     ListNode* n3_1_4 = new ListNode(9);
//     ListNode* n3_1_5 = new ListNode(9);
//     ListNode* n3_1_6 = new ListNode(9);
//     ListNode* n3_1_7 = new ListNode(9);
//     n3_1_1->next = n3_1_2;
//     n3_1_2->next = n3_1_3;
//     n3_1_3->next = n3_1_4;
//     n3_1_4->next = n3_1_5;
//     n3_1_5->next = n3_1_6;
//     n3_1_6->next = n3_1_7;
//     ListNode* n3_2_1 = new ListNode(9);
//     ListNode* n3_2_2 = new ListNode(9);
//     ListNode* n3_2_3 = new ListNode(9);
//     ListNode* n3_2_4 = new ListNode(9);
//     n3_2_1->next = n3_2_2;
//     n3_2_2->next = n3_2_3;
//     n3_2_3->next = n3_2_4;
//     result = s.addTwoNumbers(n3_1_1, n3_2_1);

//     return 0;
// }