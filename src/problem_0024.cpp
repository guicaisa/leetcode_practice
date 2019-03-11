#include <stdio.h>

/**
 * https://leetcode.com/problems/swap-nodes-in-pairs/
 */

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
	/**
	 * 使用3个节点变量，分别保存2个连续的指针，以及之后的第三个指针
	 * 交换2个连续指针的顺序，然后从第三个指针开始继续遍历
	 */
	ListNode* SwapPairs(ListNode* head) 
	{
		if (head == NULL || head->next == NULL)
		{
			return head;
		}

		ListNode* ret_head = NULL;
		ListNode* cur_node = NULL;

		while (head && head->next)
		{
			ListNode* first = head;
			ListNode* second = first->next;
			ListNode* third = second->next;

			first->next = NULL;
			second->next = first;

			if (ret_head == NULL)
			{
				ret_head = second;
				cur_node = second->next;
			}
			else
			{
				cur_node->next = second;
				cur_node = second->next;
			}

			head = third;
		}

		if (head)
		{
			cur_node->next = head;
		}

		return ret_head;
	}

	/**
	 * 使用二级指针保存第一个指针的地址，循环内交换2个指针的位置之后
	 * 将第二个指针替换为头指针，将头指针的地址更新为第一个指针的next指针的地址
	 * 作为下一次循环的第一个指针
	 */
	ListNode* SwapPairsBetter(ListNode* head)
	{
		ListNode** p = &head;
		ListNode* first = NULL;
		ListNode* second = NULL;

		while ((first = *p) && (second = first->next))
		{
			first->next = second->next;
			second->next = first;

			*p = second;
			p = &first->next;
		}

		return head;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	ListNode* node_1 = new ListNode(1);
//	ListNode* node_2 = new ListNode(2);
//	ListNode* node_3 = new ListNode(3);
//	ListNode* node_4 = new ListNode(4);
//	ListNode* node_5 = new ListNode(5);
//	
//	node_1->next = node_2;
//	node_2->next = node_3;
//	node_3->next = node_4;
//	node_4->next = node_5;
//
//	ListNode* ret = s.SwapPairsBetter(node_1);
//
//	return 0;
//}