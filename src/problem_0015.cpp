#include <stdio.h>
#include <vector>
#include <algorithm>

/**
 * https://leetcode.com/problems/3sum/
 */

class Solution {
public:
	/**
	 * 排序数组，遍历每个数字，在其之后的区间内，查找与其相加等于0的两个数
	 * 根据结果大小左移或者右移区间，在区间内去重，保存结果
	 * 同时在外层循环中去除相同的数字，防止重复计算结果
	 */
	std::vector<std::vector<int> > ThreeSum(std::vector<int>& nums) 
	{
		std::vector<std::vector<int> > result;

		if (nums.size() < 3)
		{
			return result;
		}

		std::sort(nums.begin(), nums.end());
		
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

				if (sum < 0)
				{
					++left;
				}
				else if (sum > 0)
				{
					--right;
				}
				else
				{
					std::vector<int> temp_vec;
					temp_vec.emplace_back(nums[i]);
					temp_vec.emplace_back(nums[left]);
					temp_vec.emplace_back(nums[right]);
					result.push_back(temp_vec);

					while (left + 1 < nums.size() && nums[left] == nums[left + 1])
					{
						++left;
					}

					while (right - 1 >= 0 && nums[right] == nums[right - 1])
					{
						--right;
					}

					++left;
					--right;
				}
			}
		}

		return result;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<int> nums = { -1,0,1,2,-1,-4};
//
//	std::vector<std::vector<int> > result = s.ThreeSum(nums);
//
//
//	return 0;
//}