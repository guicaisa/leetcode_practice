#include "stdio.h"

// https://leetcode.cn/problems/merge-two-sorted-lists/

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
    //同时遍历2个链表，比较两者之间的大小，将较小者放到结果链表之后
    //全部完成遍历之后，即可得到结果
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) 
    {
        ListNode* node = new ListNode();
        ListNode* dummy = node;

        while (list1 || list2)
        {
            if (list1 && (list2 == nullptr || list1->val < list2->val))
            {
                node->next = new ListNode(list1->val);
                list1 = list1->next;
            }
            else
            {
                node->next = new ListNode(list2->val);
                list2 = list2->next;
            }
            node = node->next;
        }

        return dummy->next;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     ListNode* n1_1_1 = new ListNode(1);
//     ListNode* n1_1_2 = new ListNode(2);
//     ListNode* n1_1_3 = new ListNode(4);
//     n1_1_1->next = n1_1_2;
//     n1_1_2->next = n1_1_3;
//     ListNode* n1_2_1 = new ListNode(1);
//     ListNode* n1_2_2 = new ListNode(3);
//     ListNode* n1_2_3 = new ListNode(4);
//     n1_2_1->next = n1_2_2;
//     n1_2_2->next = n1_2_3;
//     ListNode* result = s.mergeTwoLists(n1_1_1, n1_2_1);

//     ListNode* n2_1_1 = nullptr;
//     ListNode* n2_2_1 = nullptr;
//     result = s.mergeTwoLists(n2_1_1, n2_2_1);

//     ListNode* n3_1_1 = nullptr;
//     ListNode* n3_2_1 = new ListNode(0);
//     result = s.mergeTwoLists(n3_1_1, n3_2_1);

//     return 0;
// }