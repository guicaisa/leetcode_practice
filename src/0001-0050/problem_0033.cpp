#include <stdio.h>
#include <stdlib.h> 
#include <vector>

// https://leetcode-cn.com/problems/search-in-rotated-sorted-array/

class Solution 
{
public:
	// 由于数组旋转了，不是完全排序的数组，不能直接使用常规二分法
	// 每次二分的时候，需要判断左右两段哪一段是完全在一边的(就是没有跨越中间的旋转点)
	// 优先判断没有跨界的一段，判断target是否在其区间内，如果在，下一次就以这一段作为二分查找的区间，就是常规的二分查找了 
	// 如果targe不在没有跨界的那一段中，就选剩下一段，继续做二分查找，直到找出结果
	int Search(const std::vector<int>& nums, const int target)
	{
		if (nums.size() == 0)
		{
			return -1;
		}

		if (target < nums[0] && target > nums[nums.size() - 1])
		{
			return -1;
		}

		int left = 0;
		int right = nums.size() - 1;
		int mid = 0;

		while (left <= right)
		{
			mid = (left + right) / 2;
			if (nums[mid] == target)
			{
				return mid;
			}

			if (nums[left] <= nums[mid])
			{
				if (nums[left] <= target && target <= nums[mid])
				{
					right = mid - 1;
				}
				else
				{
					left = mid + 1;
				}
			}
			else
			{
				if (nums[mid] <= target && target <= nums[right])
				{
					left = mid + 1;
				}
				else
				{
					right = mid - 1;
				}
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