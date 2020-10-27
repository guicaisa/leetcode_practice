#include <stdio.h>
#include <vector>
#include <algorithm>

/**
 * https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 */

class Solution 
{
public:
	/**
	 * 使用标准库的函数将重复部分放到数组尾部，再删除
	 */
	int RemoveDuplicates(std::vector<int>& nums) 
	{
		nums.erase(std::unique(nums.begin(), nums.end()), nums.end());

		return nums.size();
	}

	/**
	 * 使用双索引，效果类似于标准库的unique函数，将重复的数字往后面排，效率更高点
	 */
	int RemoveDuplicatesBetter(std::vector<int>& nums)
	{
		if (nums.size() == 0)
		{
			return 0;
		}

		size_t i = 0;

		for (size_t j = 1; j < nums.size(); ++j)
		{
			if (nums[j] != nums[i])
			{
				++i;
				nums[i] = nums[j];
			}
		}

		return i + 1;
	}

};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<int> vec = { 0, 0, 1, 1, 2, 2, 3 };
//	
//	int ret = s.RemoveDuplicatesBetter(vec);
//
//	return 0;
//}
