#include <stdio.h>

// https://leetcode.cn/problems/remove-nth-node-from-end-of-list/

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
    //使用递归便利到尾部节点，然后返回，根据返回时的计数判断是否为单数第n个节点
    //如果是目标删除节点，则将其父节点指向该节点的子节点即可，使用dummy节点处理快速返回结果
    ListNode* removeNthFromEnd(ListNode* head, int n) 
    {
        if (head == nullptr || n == 0)
        {
            return head;
        }

        ListNode* dummy = new ListNode();
        dummy->next = head;
        this->recursive(dummy, n);

        return dummy->next;
    }

    int recursive(ListNode* node, int n) 
    {
        if (node->next == nullptr)
        {
            return 1;
        }
        int count = this->recursive(node->next, n);
        if (count == n)
        {
            ListNode* next = node->next;
            node->next = next->next;
        }
        return ++count;
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
//     ListNode* result = s.removeNthFromEnd(n1_1, 2);

//     ListNode* n2_1 = new ListNode(1);
//     result = s.removeNthFromEnd(n2_1, 1);

//     ListNode* n3_1 = new ListNode(1);
//     ListNode* n3_2 = new ListNode(2);
//     n3_1->next = n3_2;
//     result = s.removeNthFromEnd(n3_1, 1);

//     return 0;
// }