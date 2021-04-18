#include <stdio.h>

// https://leetcode-cn.com/problems/swap-nodes-in-pairs/

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
	// 使用3个节点变量，分别保存2个连续的指针，以及之后的第三个指针
	// 交换2个连续指针的顺序，将交换顺序之后的结果连接在结果链表之后，
	// 然后从第三个指针开始继续遍历，遍历的结束条件为剩余的节点个数小于2
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

	// 使用递归的方式，以2个节点为一组进行递归调用
	// 将第二个节点的next节点作为头节点进行一次递归操作
	// 交换2个节点的顺序，将返回的结果连接在交换顺序后的节点后面
	ListNode* SwapPairsRecursive(ListNode* head)
	{
		if (head == NULL || head->next == NULL)
		{
			return head;
		}

		ListNode* next = head->next;
		ListNode* next_two = head->next->next;
		ListNode* ret = this->SwapPairsRecursive(next_two);
		head->next = ret;
		next->next = head;

		return next;
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
//	ListNode* ret = s.SwapPairsRecursive(node_1);
//
//	return 0;
//}