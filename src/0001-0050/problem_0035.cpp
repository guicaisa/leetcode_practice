#include <stdio.h>
#include <stdlib.h>
#include <vector>

// https://leetcode.com/problems/search-insert-position/

class Solution 
{
public:
	// 解法就是简单的二分查找，当二分查找的循环退出的时候
	// 如果找不到目标值，那左边界就是目标值的插入点
	int SearchInsert(const std::vector<int>& nums, const int target) 
	{
		int left = 0;
		int right = nums.size() - 1;
		int mid = 0;

		while (left <= right)
		{
			mid = (left + right) / 2;

			if (nums[mid] > target)
			{
				right = mid - 1;
			}
			else if (nums[mid] < target)
			{
				left = mid + 1;
			}
			else
			{
				return mid;
			}
		}

		return left;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//	std::vector<int> vi = { 1, 3, 5, 6 };
//
//	int ret = s.SearchInsert(vi, 5);
//
//	return 0;
//}