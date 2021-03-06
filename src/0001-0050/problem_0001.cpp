#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

// https://leetcode-cn.com/problems/two-sum/

class Solution
{
public:
	
	// 第一次遍历，保存数组中的数字对应的下标到map中
 	// 第二次遍历，判断目标值与当前值的差值是否在map中，获得其下标，下标不能相同，满足条件即可得出结果 
 	// 如若输入值为{3, 3} 6 虽然map中索引值被后一个3覆盖了，但并不影响
	std::vector<int> TwoSum(const std::vector<int>& nums, const int target)                                                                
	{
		std::map<int, int> number_to_index;

		for (size_t i = 0; i < nums.size(); ++i)
		{
			number_to_index[nums[i]] = i;
		}

		for (size_t i = 0; i < nums.size(); ++i)
		{
			int differ = target - nums[i];

			if (number_to_index.find(differ) != number_to_index.end() && i != number_to_index[differ])
			{
				std::vector<int> result;
				result.emplace_back(number_to_index[differ]);
				result.emplace_back(i);
				sort(result.begin(), result.end());

				return result;
			}
		}

		return std::vector<int>(0, 0);
	}

	// 只需遍历一次的方法，仍保存数组中出现的数字对应的下标到map中
	// 但是每次遍历时，检查map中是否有与当前值组合后符合目标值的数
	// 由于题目描述已经确定只有一种解，找到匹配的结果直接返回即可
	std::vector<int> TwoSumBetter(const std::vector<int>& nums, const int target)
	{
		std::map<int, int> number_to_index;

		for (size_t i = 0; i < nums.size(); ++i)
		{
			int differ = target - nums[i];

			if (number_to_index.find(differ) != number_to_index.end())
			{
				std::vector<int> result;
				result.emplace_back(number_to_index[differ]);
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