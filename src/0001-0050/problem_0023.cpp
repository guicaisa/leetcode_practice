#include <stdio.h>
#include <vector>
#include <map>

// https://leetcode-cn.com/problems/merge-k-sorted-lists/

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
	// 将值域作为键，节点作为值，使用multimap自动排序，然后按照顺序重新连成新的链表，
	ListNode* MergeKLists(const std::vector<ListNode*>& lists) 
	{
		std::multimap<int, ListNode*> node_map;

		for (size_t i = 0; i < lists.size(); ++i)
		{
			ListNode* temp = lists[i];

			while (temp)
			{
				node_map.insert(std::make_pair(temp->val, temp));
				temp = temp->next;
			}
		}

		ListNode* head = NULL;
		ListNode* cur = NULL;
		
		if (node_map.size() > 0)
		{
			head = node_map.begin()->second;
			head->next = NULL;
			cur = head;
		}
	
		for (std::multimap<int, ListNode*>::iterator it = node_map.begin(); it != node_map.end(); ++it)
		{
			if (it == node_map.begin())
			{
				continue;
			}

			cur->next = it->second;
			cur = it->second;
			cur->next = NULL;
		}

		return head;
	}

	// 使用优先队列的方式，假设链表数组中有n个链表，我们将这n个链表的头节点以值域为键，节点为值的方式放入优先队列或者map中
	// 自动进行排序，然后取出头部的一个节点，即值域最小的节点，放入新链表中，然后将该节点的next节点再次放入优先队列或者map中
	// 不断从队列中取出头部的节点，直到所有链表遍历结束
	ListNode* MergeKListsPriorityQueue(const std::vector<ListNode*>& lists)
	{
		std::multimap<int, ListNode*> node_map;

		for (size_t i = 0; i < lists.size(); ++i)
		{
			if (lists[i])
			{
				node_map.insert(std::make_pair(lists[i]->val, lists[i]));
			}
		}

		ListNode* head = new ListNode(-1);
		ListNode* cur = head;

		while (node_map.size() > 0)
		{
			cur->next = node_map.begin()->second;
			node_map.erase(node_map.begin());
			cur = cur->next;
			if (cur->next)
			{
				node_map.insert(std::make_pair(cur->next->val, cur->next));
			}
		}

		return head->next;
	}

	// 使用分治策略，将数组不断二分进行递归，分别求解左右两部分的结果
	// 递归调用返回之后，使用MergeTwoLists的算法合并2个链表
	ListNode* MergeKListsDivideConquer(const std::vector<ListNode*>& lists)
	{
		if (lists.size() == 0)
		{
			return NULL;
		}

		return this->Recursive(lists, 0, lists.size() - 1);
	}

private:
	ListNode* Recursive(const std::vector<ListNode*>& lists, const int left, const int right)
	{
		if (left == right)
		{
			return lists[left];
		}

		if (left < right)
		{
			int mid = (left + right) / 2;
			ListNode* left_node = this->Recursive(lists, left, mid);
			ListNode* right_node = this->Recursive(lists, mid + 1, right);

			return this->MergeTwoLists(left_node, right_node);
		}

		return NULL;
	}

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
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	ListNode* node_1_1 = new ListNode(1);
//	ListNode* node_1_2 = new ListNode(4);
//	ListNode* node_1_3 = new ListNode(5);
//	node_1_1->next = node_1_2;
//	node_1_2->next = node_1_3;
//
//	ListNode* node_2_1 = new ListNode(1);
//	ListNode* node_2_2 = new ListNode(3);
//	ListNode* node_2_3 = new ListNode(4);
//	node_2_1->next = node_2_2;
//	node_2_2->next = node_2_3;
//
//	ListNode* node_3_1 = new ListNode(2);
//	ListNode* node_3_2 = new ListNode(6);
//	node_3_1->next = node_3_2;
//
//	std::vector<ListNode*> vl = { node_1_1, node_2_1, node_3_1 };
//
//	ListNode* ret = s.MergeKListsPriorityQueue(vl);
//
//	return 0;
//}