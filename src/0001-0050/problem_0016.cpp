#include <stdio.h>
#include <vector>
#include <algorithm>

// https://leetcode-cn.com/problems/3sum-closest/

class Solution 
{
public:
	// 解法与3sum类似，先排序数组，外层循环固定一个数字，然后在其之后的区间内使用双指针
	// 从首尾向中间遍历，计算三个数字的和，获得与target差值的绝对值，如果等于0，直接返回这个和
	// 使用一个变量保存最小差值和三数的和，根据大小判断更新最小的差值和三数的和
	// 如果三数之和小于target，因为数组时排好序的，后续遍历应该需要一个更大的值，左边索引向右移动
	// 如果三数之和大于target，后续遍历应该需要一个更小的值，右边索引向左移动
	// 外层循环和左右索引向中间递进的时候都需要去重，防止不必要的计算
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

			while (left < right)
			{
				int sum = nums[i] + nums[left] + nums[right];
				int temp_diff = abs(sum - target);

				if (temp_diff == 0)
				{
					return sum;
				}

				if (temp_diff < min_diff)
				{
					closest_sum = sum;
					min_diff = temp_diff;
				}

				if (sum < target)
				{
					while (left + 1 < nums.size() && nums[left] == nums[left + 1])
					{
						++left;
					}
					++left;
				}
				else if (sum > target)
				{
					while (right - 1 > i && nums[right] == nums[right - 1])
					{
						--right;
					}
					--right;
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
//	int ret = s.ThreeSumClosest(vec, 3);
//
//	return 0;
//}