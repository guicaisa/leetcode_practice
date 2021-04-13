#include <stdio.h>

// https://leetcode-cn.com/problems/merge-two-sorted-lists/

struct ListNode 
{
	ListNode(int x)
		: val(x),
		next(NULL)
	{
	}

    int val;
    ListNode* next;
};

class Solution 
{
public:
	// 使用一个头指针保存链表起始的指针，方便返回结果
	// 遍历l1和l2，比较2个指针值域的大小，从而决定指针的连接顺序
	// 如果一个链表遍历到底了，就直接将还没遍历完的链表接在新链表的后面
	ListNode* MergeTwoLists(ListNode* l1, ListNode* l2)
	{
		ListNode* head = new ListNode(-1);
		ListNode* cur = head;
		
		while (l1 && l2)
		{
			if (l1->val < l2->val)
			{
				cur->next = l1;
				l1 = l1->next;
			}
			else
			{
				cur->next = l2;
				l2 = l2->next;
			}

			cur = cur->next;
		}

		cur->next = l1 ? l1 : l2;

		return head->next;
	}

	// 使用递归的方法
	// 每层递归仍然使用一个头指针，方便返回结果
	// 核心思想是如果l1和l2都不为空的情况下，比较l1和l2的值域大小
	// 较小的那一个指针，向下递进一步，将l1->next和l2或者l1和l2->next作为下一级递归函数的变量
	// 不断递归调用，求出最终结果，当然也要考虑l1和l2同时为空或者其中有一个为空的特殊情况
	ListNode* MergeTwoListsRecursive(ListNode* l1, ListNode* l2)
	{
		return this->Recursive(l1, l2);
	}

private:
	ListNode* Recursive(ListNode* l1, ListNode* l2)
	{
		ListNode* head = new ListNode(-1);

		if (l1 == NULL && l2 == NULL)
		{
			head->next = NULL;
		}
		else if (l1 == NULL)
		{
			head->next = l2;
		}
		else if (l2 == NULL)
		{
			head->next = l1;
		}
		else
		{
			if (l1->val < l2->val)
			{
				head->next = l1;
				head->next->next = this->Recursive(l1->next, l2);
			}
			else
			{
				head->next = l2;
				head->next->next = this->Recursive(l1, l2->next);
			}
		}

		return head->next;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	ListNode* node_1_1 = new ListNode(-9);
//	ListNode* node_1_2 = new ListNode(3);
//	ListNode* node_1_3 = new ListNode(4);
//	node_1_1->next = node_1_2;
//	//node_1_2->next = node_1_3;
//
//	ListNode* node_2_1 = new ListNode(5);
//	ListNode* node_2_2 = new ListNode(7);
//	ListNode* node_2_3 = new ListNode(4);
//	node_2_1->next = node_2_2;
//	//node_2_2->next = node_2_3;
//
//	ListNode* ret = s.MergeTwoLists(node_1_1, node_2_1);
//
//	return 0;
//}