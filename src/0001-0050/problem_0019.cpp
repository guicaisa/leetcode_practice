#include <stdio.h>

// https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/

struct ListNode 
{
    int val;
    ListNode* next;

    ListNode(int x) 
		: val(x), 
		next(NULL) 
	{
	}
 };

class Solution 
{
public:
	// 先遍历一次计算链表长度，然后再遍历一次找到那个节点进行删除
	ListNode* RemoveNthFromEnd(ListNode* head, int n) 
	{
		ListNode* temp = head;
		int num = 0;

		while (temp)
		{
			++num;
			temp = temp->next;
		}

		if (num == n)
		{
			head = head->next;
		}
		else
		{
			num -= n;
			temp = head;

			while (temp)
			{
				if (--num <= 0)
				{
					temp->next = temp->next->next;
					break;
				}
				else
				{
					temp = temp->next;
				}
			}
		}

		return head;
	}

	// 递归解法，先递归到尾节点，然后减少n的值，当n为0时
	// 将当前节点的下一节点作为当前节点返回给上层，从而达到删除该节点的目的
	ListNode* RemoveNthFromEndRecursive(ListNode* head, int n)
	{
		num_ = n;

		return this->Recursive(head);
	}

	// 使用快慢双指针只进行一次遍历，其中一个是二级指针，根据n的大小，先将一级指针递进n-1次
	// 之后双指针一起递进移动，在一级指针移动到尾端之后，二级指针此时指向的即为倒数第n个节点
	// 直接将其之后的节点赋值给二级指针的解引用，完成删除节点
	ListNode* RemoveNthFromEndBetter(ListNode* head, int n)
	{
		ListNode** p = &head;
		ListNode* temp = head;
		int count = n - 1;

		while (temp->next)
		{
			if (count <= 0)
			{
				p = &((*p)->next);
			}
			else
			{
				--count;
			}
			
			temp = temp->next;
		}

		(*p) = (*p)->next;

		return head;
	}

private:
	ListNode* Recursive(ListNode* head)
	{
		ListNode* temp = NULL;

		if (head->next)
		{
			temp = this->Recursive(head->next);
		}

		if (--num_ == 0)
		{
			head = temp;
		}
		else
		{
			head->next = temp;
		}

		return head;
	}

	int num_;
};

//int main(int argc, char** argv)
//{
//	ListNode* node_1 = new ListNode(1);
//	ListNode* node_2 = new ListNode(2);
//	ListNode* node_3 = new ListNode(3);
//	ListNode* node_4 = new ListNode(4);
//	ListNode* node_5 = new ListNode(5);
//
//	/*node_1->next = node_2;
//	node_2->next = node_3;
//	node_3->next = node_4;
//	node_4->next = node_5;*/
//
//	Solution s;
//	ListNode* ret = s.RemoveNthFromEndRecursive(node_1, 1);
//
//	return 0;
//}