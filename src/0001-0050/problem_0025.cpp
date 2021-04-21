#include <stdio.h>

// https://leetcode-cn.com/problems/reverse-nodes-in-k-group/

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
	// 使用一个多余的头指针来保存最终的结果，使用一个pre指针来辅助处理连续k个节点交换顺序
	// 遍历链表，使用计数变量，在遍历每k个节点之后，保存尾节点的next指针，倒置该k个节点的顺序
	// 将原来的头节点，即现在的尾节点的next设置为之前保存的next
	// 将原来的尾节点，即现在的头节点放在pre指针的next域，即完成k个节点的交换顺序
	// 并将倒序后的节点重新接入已有的链表中
	ListNode* ReverseKGroup(ListNode* head, int k)
	{
		ListNode* n = new ListNode(-1);
		n->next = head;
		ListNode* pre = n;
		ListNode* cur = head;
		int count = 0;
		
		while (cur)
		{
			++count;
			if (count == k)
			{
				// 此处cur为k个节点中的尾节点，保存next
				ListNode* next = cur->next;
				cur->next = NULL;
				// 此处first为k个节点中的头节点
				ListNode* first = pre->next;
				// 倒置顺序
				this->ReverseNode(first);
				// 此处的first已经变为尾节点，将保存的next赋值给其next域
				first->next = next;
				// 此处的cur已经变为头节点，将其赋值给pre的next域
				pre->next = cur;

				// 当前的尾节点作为下一轮k个节点的pre节点
				pre = first;
				cur = pre->next;
				count = 0;
			}
			else
			{
				cur = cur->next;
			}
		}

		return n->next;
	}

	// 与第一个方法是相同的思路，只不过把中间倒顺链表的方式从递归改成了遍历
	ListNode* ReverseKGroupIterate(ListNode* head, int k)
	{
		ListNode* n = new ListNode(-1);
		n->next = head;
		ListNode* pre = n;
		ListNode* cur = head;
		int count = 0;

		while (cur)
		{
			++count;
			cur = cur->next;
		}

		cur = head;
		while (count >= k)
		{
			for (int i = 1; i < k; ++i)
			{
				// 这里的cur永远是k个节点中的第一个节点
				// 整个循环不断把cur往后移
				// cur的next即下一个要调到头部的节点
				ListNode* next = cur->next;
				// cur的next变成后面隔一个节点
				cur->next = next->next;
				// next即将被放在k个节点的头部，将当前的头部节点当作自己的next
				next->next = pre->next;
				// 将next放在k个节点的第一个位置上
				pre->next = next;
			}

			// 下一轮
			pre = cur;
			cur = pre->next;

			count -= k;
		}

		return n->next;
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
//	ListNode* ret = s.ReverseKGroupIterate(node_1, 2);
//
//	return 0;
//}