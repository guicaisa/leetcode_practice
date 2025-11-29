#include <stdio.h>

// https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/

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
    //遍历节点记录数值出现的次数，遇到不同值节点时，检查前一个节点值是否出现了多次
    //如果是就略过，如果是单个值的节点，就链在前置节点之后，并将其本身设置为前置节点进入下一个循环
    //完成循环之后需要注意将前置节点的next设置为空
    ListNode* deleteDuplicates(ListNode* head) 
    {
        if (head == nullptr)
        {
            return nullptr;
        }

        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* pre_node = dummy;
        int count = 0;
        while (head)
        {
            if (head->next == nullptr)
            {
                if (count == 0)
                {
                    pre_node->next = head;
                    pre_node = head;
                }
                break;
            }

            if (head->val != head->next->val)
            {
                if (count == 0)
                {
                    pre_node->next = head;
                    pre_node = head;
                }
                else 
                {
                    count = 0;
                }
                
                head = head->next;
                continue;
            }
            ++count;
            head = head->next;
        }

        pre_node->next = nullptr;

        return dummy->next;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     ListNode* n1_1 = new ListNode(1);
//     ListNode* n1_2 = new ListNode(2);
//     ListNode* n1_3 = new ListNode(3);
//     ListNode* n1_4 = new ListNode(3);
//     ListNode* n1_5 = new ListNode(4);
//     ListNode* n1_6 = new ListNode(4);
//     ListNode* n1_7 = new ListNode(5);
//     n1_1->next = n1_2;
//     n1_2->next = n1_3;
//     n1_3->next = n1_4;
//     n1_4->next = n1_5;
//     n1_5->next = n1_6;
//     n1_6->next = n1_7;
//     ListNode* result = s.deleteDuplicates(n1_1);

//     ListNode* n2_1 = new ListNode(1);
//     ListNode* n2_2 = new ListNode(1);
//     ListNode* n2_3 = new ListNode(1);
//     ListNode* n2_4 = new ListNode(2);
//     ListNode* n2_5 = new ListNode(3);
//     n2_1->next = n2_2;
//     n2_2->next = n2_3;
//     n2_3->next = n2_4;
//     n2_4->next = n2_5;
//     result = s.deleteDuplicates(n2_1);

//     return 0;
// }