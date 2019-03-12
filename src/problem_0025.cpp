#include <stdio.h>

/**
 * https://leetcode.com/problems/reverse-nodes-in-k-group/
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
	 * 使用二级指针保存头部节点指针的位置，用来更新置换顺序之后的头部节点
	 * 使用计数变量，在遍历每k个节点之后，倒置该k个节点的顺序，将当前节点
	 * 即倒置之后的头结点赋值给二级指针的解引用，达到替换头节点的目的
	 * 将之前的头节点，即倒置之后的尾节点的next域的指针重新赋值给二级指针
	 * 在下一次遍历过程中作为下一组节点连接的头节点，倒置节点使用的是递归的方式
	 */
	ListNode* ReverseKGroup(ListNode* head, int k)
	{
		ListNode** p = &head;
		ListNode* front_node = head;
		ListNode* cur_node = head;
		int count = 0;

		while (cur_node)
		{
			++count;

			if (count == k)
			{
				//保存下一段节点的开头
				ListNode* next_node = cur_node->next;
				cur_node->next = NULL;

				ListNode* tail_node = this->ReverseNode(front_node);
				//当前节点已经是头节点了
				*p = cur_node;
				//尾节点就是倒置之前的头节点，其next域作为下一段节点的连接头
				p = &tail_node->next;

				//重置变量，开启新一轮遍历计数
				cur_node = next_node;
				front_node = next_node;
				count = 0;
			}
			else
			{
				cur_node = cur_node->next;
			}
		}

		if (count > 0 && count < k)
		{
			*p = front_node;
		}

		return head;
	}

	/**
	 * 与第一个函数功能相同，只是把倒置节点的函数从递归改成了循环，
	 * 使用二级指针保存头节点的位置，用赋值解引用的方式完成头节点的替换，耗时会低一些
	 */
	ListNode* ReverseKGroupBetter(ListNode* head, int k) 
	{
		ListNode** p = &head;
		ListNode* front_node = head;
		ListNode* cur_node = head;
		int count = 0;

		while (cur_node)
		{
			++count;

			if (count == k)
			{
				//保存下一段节点的开头
				ListNode* next_node = cur_node->next;
				cur_node->next = NULL;

				this->ReverseNodeOth(front_node, k);
				//当前节点已经是头节点了
				*p = cur_node;
				//头节点在倒置之后已经成为了尾节点，其next域作为下一段节点的连接头
				p = &front_node->next;

				//重置变量，开启新一轮遍历计数
				cur_node = next_node;
				front_node = next_node;
				count = 0;
			}
			else
			{
				cur_node = cur_node->next;
			}
		}

		if (count > 0 && count < k)
		{
			*p = front_node;
		}

		return head;
	}

private:
	ListNode* ReverseNode(ListNode* node)
	{
		if (node->next == NULL)
		{
			return node;
		}

		ListNode* cur_node = this->ReverseNode(node->next);
		cur_node->next = node;
		node->next = NULL;

		return node;
	}

	ListNode* ReverseNodeOth(ListNode* head, int k)
	{
		ListNode** p_head = &head;
		ListNode* cur_node = head;

		for (int i = 1; i < k; ++i)
		{
			ListNode* next_node = cur_node->next;
			ListNode* temp_node = next_node->next;

			next_node->next = *p_head;
			cur_node->next = temp_node;

			*p_head = next_node;
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
//
//	ListNode* ret = s.ReverseKGroup(node_1, 3);
//
//	return 0;
//}