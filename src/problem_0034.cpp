#include <stdio.h>
#include <stdlib.h>
#include <vector>

class Solution 
{
public:
	// 用二分查找，在找到目标值的情况下，以当前索引为基础，向左右延伸
	// 继续进行二分查找，直到找不到目标值为止，确定左右边界，得出结果
	std::vector<int> SearchRange(const std::vector<int>& nums, const int target)
	{
		int first = FindTarget(nums, target, 0, nums.size() - 1);

		if (first == -1)
		{
			return std::vector<int>(2, -1);
		}

		int left_end = first;
		int right_end = first;
		int left = 0;
		int right = 0;
		int mid = 0;

		left = 0;
		right = first - 1;
		
		while (1)
		{
			mid = FindTarget(nums, target, left, right);
			if (mid != -1)
			{
				right = mid - 1;
				left_end = mid;
			}
			else
			{
				break;
			}
		}

		left = first + 1;
		right = nums.size() - 1;
		
		while (1)
		{
			mid = FindTarget(nums, target, left, right);
			if (mid != -1)
			{
				left = mid + 1;
				right_end = mid;
			}
			else
			{
				break;
			}
		}
		
		return std::vector<int>{left_end, right_end};
	}


	int FindTarget(const std::vector<int>& nums, const int target, int left, int right)
	{
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

		return -1;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<int> vi = { 5, 7, 7, 8, 8, 10 };
//
//	std::vector<int> ret = s.SearchRange(vi, 6);
//
//	return 0;
//}