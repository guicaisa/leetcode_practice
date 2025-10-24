#include "stdio.h"

// https://leetcode.cn/problems/linked-list-cycle/

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution 
{
public:
    //1. 双指针
    //使用快慢指针同时遍历链表，如果快慢指针指向了同一个节点，则表示链表有环
    bool hasCycle(ListNode *head) 
    {
        if (head == nullptr || head->next == nullptr)
        {
            return false;
        }

        ListNode* p1 = head;
        ListNode* p2 = head;
        
        while (p1 && p2)
        {
            p1 = p1->next;
            p2 = p2->next;
            if (p2)
            {
                p2 = p2->next;
            }
            if (p1 == p2)
            {
                return true;
            }
        }

        return false;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     ListNode* n1_1 = new ListNode(3);
//     ListNode* n1_2 = new ListNode(2);
//     ListNode* n1_3 = new ListNode(0);
//     ListNode* n1_4 = new ListNode(-4);
//     n1_1->next = n1_2;
//     n1_2->next = n1_3;
//     n1_3->next = n1_4;
//     n1_4->next = n1_2;
//     bool result = s.hasCycle(n1_1);

//     ListNode* n2_1 = new ListNode(1);
//     ListNode* n2_2 = new ListNode(2);
//     n2_1->next = n2_2;
//     n2_2->next = n2_1;
//     result = s.hasCycle(n2_1);

//     ListNode* n3_1 = new ListNode(1);
//     result = s.hasCycle(n3_1);

//     return 0;
// }