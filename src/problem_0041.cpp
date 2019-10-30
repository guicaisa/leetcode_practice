#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

/**
 * https://leetcode.com/problems/first-missing-positive/
 */

class Solution 
{
public:
	/**
	 * 描述的部分有点看不懂，实际上题目的意思是一个数组，假设长度为4
	 * 那么正常情况下其中的元素应该是1，2，3，4
	 * 但实际情况数组是1，5，3，4，找出最小的消失的正整数，即为2
	 * 这个数组在正常情况下(1，2，3，4)有个特点，即nums[i] = i + 1
	 * 一般情况下，需要对数组进行排序，但是题目中不允许使用额外的空间
	 * 根据nums[i] = i + 1公式，使用数组本身作为存储介质
	 * 在遍历过程中根据公式将乱序的数组元素放到原来的位置上
	 * 如3，4，-1，1 根据元素的值找到其对应的索引位置，如nums[0] = 3
	 * 值为3，其位置应该是nums[2],对比nums[0]和nums[0]发现值并不相等
	 * 对调位置，将3放回到nums[2]的位置上，依此遍历，得到结果1，-1，3，4
	 * 最终发现缺少的最小正数为2
	 */
	int FirstMissingPositive(std::vector<int>& nums) 
	{
		for (int i = 0; i < nums.size(); ++i)
		{
			while (nums[i] > 0 && nums[i] <= nums.size() && nums[nums[i] - 1] != nums[i])
			{
				std::swap(nums[i], nums[nums[i] - 1]);
			}
		}

		for (int i = 0; i < nums.size(); ++i)
		{
			if (nums[i] - 1 != i)
			{
				return i + 1;
			}
		}

		return nums.size() + 1;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<int> vi = {7, 8, 9, 11, 12};
//
//	int ret = s.FirstMissingPositive(vi);
//
//	return 0;
//}