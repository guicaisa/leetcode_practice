#include <stdio.h>
#include <vector>

// https://leetcode-cn.com/problems/remove-element/

class Solution 
{
public:
	// 使用双指针的方法，固定一个指针索引不动，用另一个索引去遍历数组
	// 判断是否与目标值相同，不相同才将值更新到第一个指针索引的位置
	// 否则略过，与problem.26类似
	int RemoveElement(std::vector<int>& nums, int val) 
	{
		int i = 0;

		for (int j = 0; j < nums.size(); ++j)
		{
			if (nums[j] != val)
			{
				nums[i] = nums[j];
				++i;
			}
		}

		return i;
	}

	// 另一种双指针的方法，第一个指针从头遍历，第二指针先定位在数组末尾处
	// 遇到与目标值相同的数字第一个指针不动，与第二个指针的元素互换位置，第二个指针向左移动
	// 遇到与目标值不同的数字第一个指针继续向右移动，第二个指针不动
	// 实际上就是将与目标值相同的数字全部移动到数组的末尾处
	int RemoveElementOther(std::vector<int>& nums, int val)
	{
		if (nums.size() == 0)
		{
			return 0;
		}

		int i = 0;
		int j = nums.size() - 1;
		for (; i < nums.size() && j >= i; )
		{
			if (nums[i] == val)
			{
				int temp = nums[j];
				nums[j] = nums[i];
				nums[i] = temp;
				--j;
			}
			else
			{
				++i;
			}
		}

		return i;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//	std::vector<int> nums = { 3, 2, 2, 3 };
//
//	int ret = s.RemoveElement(nums, 3);
//
//	return 0;
//}