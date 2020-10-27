#include <stdio.h>
#include <vector>
#include <map>

/**
 * https://leetcode.com/problems/merge-k-sorted-lists/
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
	 * 使用multimap自动排序，然后重新链成新的链表
	 */
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

	/**
	 * 使用分治策略，使用MergeTwoLists的算法分开计算每两个指针，得到最终结果
	 */
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
//	ListNode* ret = s.MergeKListsBetter(vl);
//
//	return 0;
//}