#include "stdio.h"

// https://leetcode.cn/problems/reverse-linked-list-ii/

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
    //遍历整个链表，在符合左区间的位置开始进行递归调用，在右边界的位置结束递归
    //递归函数将整个链表进行反转，并链回原链表中
    ListNode* reverseBetween(ListNode* head, int left, int right) 
    {
        ListNode* dummy = new ListNode(head->val - 1);
        dummy->next = head;
        ListNode* pre_node = dummy;
        int count = 0;
        while (head)
        {
            if (++count < left)
            {
                pre_node = head;
                head = head->next;
                continue;
            }
            ListNode* temp = this->findRightNode(head, right, count);
            pre_node->next = temp;
            break;
        }

        return dummy->next;
    }

    ListNode* findRightNode(ListNode* node, int right, int count)
    {
        if (node->next == nullptr || count+1 > right)
        {
            return node;
        }
        ListNode* temp = this->findRightNode(node->next, right, count+1);
        ListNode* next = node->next;
        node->next = next->next;
        next->next = node;
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
//     ListNode* result = s.reverseBetween(n1_1, 2, 4);

//     ListNode* n2_1 = new ListNode(5);
//     result = s.reverseBetween(n2_1, 1, 1);

//     return 0;
// }