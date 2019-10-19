#include <stdio.h>
#include <stdlib.h> 
#include <vector>

/**
 * https://leetcode.com/problems/search-in-rotated-sorted-array/
 */

class Solution 
{
public:
	// 由于数组旋转了，不是完全排序的数组，不能直接使用常规二分法
	// 以数组旋转的索引为中间点，判断目标值存在于数组左边还是右边
	// 二分查找的时候，根据中间值与目标值是否处于一边，判断下次下分的边界(往左还是往右)
	// 当中间值与目标值处于同一边时，使用正常二分查找判断大小即可
	int Search(const std::vector<int>& nums, const int target) 
	{
		if (nums.size() == 0)
		{
			return -1;
		}

		int left_flag = 0;
		int right_flag = 0;

		if (target >= nums[0])
		{
			left_flag = 1;
		}
		else if (target <= nums[nums.size() - 1])
		{
			right_flag = 1;
		}
		else
		{
			return -1;
		}

		int left = 0;
		int right = nums.size() - 1;
		int mid = 0;

		while (left <= right)
		{
			mid = (left + right) / 2;
			if (left_flag == 1 && nums[mid] < nums[0] && nums[mid] <= nums[nums.size() - 1])
			{
				right = mid - 1;
			}
			else if (right_flag == 1 && nums[mid] >= nums[0] && nums[mid] > nums[nums.size() - 1])
			{
				left = mid + 1;
			}
			else if (nums[mid] > target)
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
//	std::vector<int> vi = {3, 1};
//
//	Solution s;
//
//	int ret = s.Search(vi, 1);
//
//	return 0;
//}