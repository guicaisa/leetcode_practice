#include <stdio.h>

// https://leetcode.cn/problems/rotate-list/

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
    // 1. 两次遍历
    //第一次遍历，计算出链表长度，第二次遍历找到移动的那个节点，然后重新链接下，即可
    ListNode* rotateRight(ListNode* head, int k) 
    {
        if (head == nullptr || k == 0)
        {
            return head;
        }

        ListNode* node = head;
        ListNode* tail = nullptr;
        int n = 0;
        while (node)
        {
            ++n;
            tail = node;
            node = node->next;
        }
        int shift = k % n;
        if (shift == 0)
        {
            return head;
        }

        node = head;
        ListNode* pre_node = nullptr;
        int shift_reverse = n - shift;
        int count = 0;
        while (node)
        {
            if (count == shift_reverse)
            {
                break;
            }
            pre_node = node;
            node = node->next;
            ++count;
        }

        pre_node->next = nullptr;
        tail->next = head;
        return node;
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
//     ListNode* result = s.rotateRight(n1_1, 2);

//     ListNode* n2_1 = new ListNode(0);
//     ListNode* n2_2 = new ListNode(1);
//     ListNode* n2_3 = new ListNode(2);
//     n2_1->next = n2_2;
//     n2_2->next = n2_3;
//     result = s.rotateRight(n2_1, 4);

//     return 0;
// }