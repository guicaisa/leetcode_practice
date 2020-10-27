#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

/**
 * https://leetcode.com/problems/two-sum/
 */

class Solution
{
public:
	/**
	 * 一次遍历保存数组中出现的数字对应的索引
	 * 二次遍历找出目标值与当前值的差值是否在数组中，获得其索引，注意不能是当前值本身 
	 * 如若输入值为{3, 3} 6 虽然映射中索引值被后一个3覆盖了，但并不影响结果
	 */
	std::vector<int> TwoSum(const std::vector<int>& nums, const int target)                                                                
	{
		std::map<int, int> number_to_index;

		for (size_t i = 0; i < nums.size(); ++i)
		{
			number_to_index[nums[i]] = i;
		}

		for (size_t i = 0; i < nums.size(); ++i)
		{
			if (number_to_index.find(target - nums[i]) != number_to_index.end() && i != number_to_index[target - nums[i]])
			{
				std::vector<int> result;
				result.emplace_back(number_to_index[target - nums[i]]);
				result.emplace_back(i);
				sort(result.begin(), result.end());

				return result;
			}
		}

		return std::vector<int>(0, 0);
	}

	/**
	 * 只需遍历一次的方法，仍保存数组中出现的数字对应的索引
	 * 但是每次遍历时，检查映射中是否有与当前值组合后符合目标值的数
	 * 由于题目描述已经确定只有一种解，找到匹配的结果直接返回即可
	 */
	std::vector<int> TwoSumBetter(const std::vector<int>& nums, const int target)
	{
		std::map<int, int> number_to_index;

		for (size_t i = 0; i < nums.size(); ++i)
		{
			if (number_to_index.find(target - nums[i]) != number_to_index.end())
			{
				std::vector<int> result;
				result.emplace_back(number_to_index[target - nums[i]]);
				result.emplace_back(i);

				return result;
			}

			number_to_index[nums[i]] = i;
		}

		return std::vector<int>(0, 0);
	}
};


//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<int> test_vec = { 3, 3 };
//	std::vector<int> result;
//
//	result = s.TwoSum(test_vec, 6);
//
//	return 0;
//}