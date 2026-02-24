#include <stdio.h>

// https://leetcode.cn/problems/sort-list/

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
    //1. 递归+二分
    //将链表一分为二，左右两部分进行递归调用，然后将结果用归并排序进行处理
    ListNode* sortList(ListNode* head) 
    {
        if (head == nullptr)
        {
            return nullptr;
        }

        ListNode* node = head;
        int cnt = 0;
        while (node)
        {
            ++cnt;
            node = node->next;
        }
        if (cnt == 1)
        {
            return head;
        }

        int mid = cnt / 2;
        cnt = 0;
        node = head;
        ListNode* left = nullptr;
        ListNode* right = nullptr;
        while (1)
        {
            if (++cnt == mid)
            {
                ListNode* right_head = node->next;
                node->next = nullptr;
                left = this->sortList(head);
                right = this->sortList(right_head);
                break;
            }
            node = node->next;
        }

        node = nullptr;
        ListNode* dummy = new ListNode();
        while (left || right)
        {
            ListNode* temp = nullptr;
            if (left && right)
            {
                if (left->val < right->val)
                {
                    temp = left;
                    left = left->next;
                }
                else
                {
                    temp = right;
                    right = right->next;
                }
            }
            else if (left)
            {
                temp = left;
                left = left->next;
            }
            else
            {
                temp = right;
                right = right->next;
            }
            temp->next = nullptr;
            if (node == nullptr)
            {
                node = temp;
                dummy->next = node;
            }
            else
            {
                node->next = temp;
                node = temp;
            }
        }

        return dummy->next;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：head = [4,2,1,3]
//     //输出：[1,2,3,4]
//     ListNode* n1_1 = new ListNode(4);
//     ListNode* n1_2 = new ListNode(2);
//     ListNode* n1_3 = new ListNode(1);
//     ListNode* n1_4 = new ListNode(3);
//     n1_1->next = n1_2;
//     n1_2->next = n1_3;
//     n1_3->next = n1_4;
//     ListNode* result = s.sortList(n1_1);

//     //输入：head = [-1,5,3,4,0]
//     //输出：[-1,0,3,4,5]
//     ListNode* n2_1 = new ListNode(-1);
//     ListNode* n2_2 = new ListNode(5);
//     ListNode* n2_3 = new ListNode(3);
//     ListNode* n2_4 = new ListNode(4);
//     ListNode* n2_5 = new ListNode(0);
//     n2_1->next = n2_2;
//     n2_2->next = n2_3;
//     n2_3->next = n2_4;
//     n2_4->next = n2_5;
//     result = s.sortList(n2_1);

//     //输入：head = []
//     //输出：[]
//     result = s.sortList(nullptr);

//     return 0;
// }