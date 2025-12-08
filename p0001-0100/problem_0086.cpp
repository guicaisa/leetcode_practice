#include <stdio.h>

// https://leetcode.cn/problems/partition-list/

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
    //1. 遍历+双指针
    //使用左右两个指针保存两侧的节点，遍历原链表，根据大小关系分别链在左右节点之后
    //遍历完之后将右边链表链接在左边链表的后面，然后返回左边链表即得到结果
    ListNode* partition(ListNode* head, int x)
    {
        if (head == nullptr)
        {
            return nullptr;
        }
        
        ListNode* dummy_left = new ListNode();
        ListNode* dummy_right = new ListNode();
        ListNode* node_left = nullptr;
        ListNode* node_right = nullptr;
        while (head)
        {
            if (head->val < x)
            {
                if (node_left == nullptr)
                {
                    dummy_left->next = head;
                }
                else
                {
                    node_left->next = head;
                }
                node_left = head;
            }
            else
            {
                if (node_right == nullptr)
                {
                    dummy_right->next = head;
                }
                else
                {
                    node_right->next = head;
                }
                node_right = head;
            }
            head = head->next;
        }
        if (node_right)
        {
            node_right->next = nullptr;
        }
        if (node_left)
        {
            node_left->next = dummy_right->next;
        }
        else
        {
            dummy_left->next = dummy_right->next;
        }

        return dummy_left->next;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     ListNode* n1_1 = new ListNode(1);
//     ListNode* n1_2 = new ListNode(4);
//     ListNode* n1_3 = new ListNode(3);
//     ListNode* n1_4 = new ListNode(2);
//     ListNode* n1_5 = new ListNode(5);
//     ListNode* n1_6 = new ListNode(2);
//     n1_1->next = n1_2;
//     n1_2->next = n1_3;
//     n1_3->next = n1_4;
//     n1_4->next = n1_5;
//     n1_5->next = n1_6;
//     ListNode* result = s.partition(n1_1, 3);

//     ListNode* n2_1 = new ListNode(2);
//     ListNode* n2_2 = new ListNode(1);
//     n2_1->next = n2_2;
//     result = s.partition(n2_1, 2);

//     ListNode* n3_1 = new ListNode(1);
//     result = s.partition(n3_1, 0);

//     return 0;
// }