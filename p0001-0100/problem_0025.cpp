#include <stdio.h>

// https://leetcode.cn/problems/reverse-nodes-in-k-group/

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
    //1. 递归
    //遍历整个链表，每k个节点进行一次链表倒置，并将倒置后的结果链回原链表中
    ListNode* reverseKGroup(ListNode* head, int k) 
    {
        if (k <= 1)
        {
            return head;
        }
        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* node = dummy;
        while (1)
        {
            if (node->next == nullptr)
            {
                break;
            }
            ListNode* temp = this->recursive(node->next, k, 1);
            if (temp == nullptr)
            {
                break;
            }
            ListNode* next = node->next;
            node->next = temp;
            node = next;
        }
        return dummy->next;
    }

    ListNode* recursive(ListNode* node, int k, int count)
    {
        if (count >= k)
        {
            return node;
        }
        if (node->next == nullptr)
        {
            return nullptr;
        }
        ListNode* temp = this->recursive(node->next, k, count+1);
        if (temp != nullptr)
        {
            ListNode* next = node->next->next;
            node->next->next = node;
            node->next = next;
        }
        return temp;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     ListNode* n1_1 = new ListNode(1);
//     ListNode* n1_2 = new ListNode(2);
//     ListNode* n1_3 = new ListNode(3);
//     ListNode* n1_4 = new ListNode(4);
//     ListNode* n1_5 = new ListNode(5);
//     n1_1->next = n1_2;
//     n1_2->next = n1_3;
//     n1_3->next = n1_4;
//     n1_4->next = n1_5;
//     ListNode* result = s.reverseKGroup(n1_1, 2);

//     ListNode* n2_1 = new ListNode(1);
//     ListNode* n2_2 = new ListNode(2);
//     ListNode* n2_3 = new ListNode(3);
//     ListNode* n2_4 = new ListNode(4);
//     ListNode* n2_5 = new ListNode(5);
//     n2_1->next = n2_2;
//     n2_2->next = n2_3;
//     n2_3->next = n2_4;
//     n2_4->next = n2_5;
//     result = s.reverseKGroup(n2_1, 3);

//     ListNode* n3_1 = new ListNode(1);
//     ListNode* n3_2 = new ListNode(2);
//     n3_1->next = n3_2;
//     result = s.reverseKGroup(n3_1, 2);

//     return 0;
// }