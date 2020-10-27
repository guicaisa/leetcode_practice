#include <stdio.h>

/**
 * https://leetcode.com/problems/merge-two-sorted-lists/
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
	 * 遍历2个指针，根据值域的大小安排其节点在新链表中的位置
	 * 如果一个链表遍历到底了，就直接将还没遍历完的链表直接接在新链表的后面
	 */
	ListNode* MergeTwoLists(ListNode* l1, ListNode* l2)
	{
		ListNode* result = NULL;
		ListNode* cur_node = NULL;

		while (l1 || l2)
		{
			ListNode* temp = NULL;

			if (l1 && l2)
			{
				if (l1->val < l2->val)
				{
					temp = l1;
					l1 = l1->next;
				}
				else
				{
					temp = l2;
					l2 = l2->next;
				}
			}
			else if (l1)
			{
				if (result)
				{
					cur_node->next = l1;
				}
				else
				{
					result = l1;
				}
				break;

			}
			else if (l2)
			{
				if (result)
				{
					cur_node->next = l2;
				}
				else
				{
					result = l2;
				}
				break;
			}

			temp->next = NULL;

			if (result == NULL)
			{
				result = temp;
			}
			else
			{
				cur_node->next = temp;
			}
			cur_node = temp;
		}

		return result;
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