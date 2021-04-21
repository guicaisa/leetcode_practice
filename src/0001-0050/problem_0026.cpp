#include <stdio.h>
#include <vector>
#include <algorithm>

// https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/

class Solution 
{
public:
	// 使用双指针，将一个指针固定在不重复的数字索引处
	// 另一个指针遍历数组，如果遇到不重复的数字，就递进第一个索引
	// 如果遇到重复的数字，第一个指针停止不动，移动第二个指针直到遇到不重复的数字
	// 放到第一个指针之后，遍历结束，返回第一个指针索引的值+1就是所有不重复数字的个数
	int RemoveDuplicates(std::vector<int>& nums) 
	{
		if (nums.size() == 0)
		{
			return 0;
		}

		size_t i = 0;
		for (size_t j = 1; j < nums.size(); ++j)
		{
			if (nums[i] != nums[j])
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
