#include <stdio.h>
#include <vector>
#include <algorithm>

/**
 * https://leetcode.com/problems/3sum-closest/
 */

class Solution 
{
public:
	/**
	 * 解法与3sum类似，先排序数组，使用左右边界，只有在外层循环需要去重
	 * 根据3个数的和与目标数比较是大还是小，如果大就将右边界往左移
	 * 如果小，就将左边界往右移，相同就直接返回，有且只有一个解
	 * 内层不需要判断去重
	 */
	int ThreeSumClosest(std::vector<int>& nums, const int target) 
	{
		if (nums.size() == 0)
		{
			return 0;
		}

		sort(nums.begin(), nums.end());

		int min_diff = INT_MAX;
		int closest_sum = 0;

		for (size_t i = 0; i < nums.size(); ++i)
		{
			if (i > 0 && nums[i] == nums[i - 1])
			{
				continue;
			}

			int left = i + 1;
			int right = nums.size() - 1;
			int temp_min_diff = INT_MAX;
			int temp_closest_sum = 0;

			while (left < right)
			{
				int sum = nums[i] + nums[left] + nums[right];

				if (abs(sum - target) < temp_min_diff)
				{
					temp_closest_sum = sum;
					temp_min_diff = abs(sum - target);
				}

				if (sum < target)
				{
					++left;
				}
				else if (sum > target)
				{
					--right;
				}
				else
				{
					return sum;
				}

				if (temp_min_diff < min_diff)
				{
					min_diff = temp_min_diff;
					closest_sum = temp_closest_sum;
				}
			}
		}

		return closest_sum;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<int> vec = { -1, 0, 1, 1, 55 };
//
//
//	int ret = s.ThreeSumClosest(vec, 3);
//
//
//
//	return 0;
//}