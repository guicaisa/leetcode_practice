#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

// https://leetcode-cn.com/problems/next-permutation/

class Solution
{
public:
	// 根据肉眼观察，寻找下一个数字排列，需要从数组的右边开始寻找第一组
	// 是升序形式的2个数字，将其进行交换才能使得下一次的数字排列有可能是更大的
	// 比如1，2，3，4，从最右边开始找到的第一个升序排列的2个数字是3，4，交换3和4
	// 获得下一个数字排列，1，2，4，3
	// 如果是另一种复杂的情况，比如1，4，3，2，从右开始找到第一组升序排列的数字是1，4
	// 这里不能直接交换1和4的位置，因为4后面还有其他比4小的数字，如果是4，1，3，2的话明显
	// 结果是不对的，因为中间还有很多次大一点的排列没有列举出来
	// 遇到这种情况，应该从尾遍历到1之前的所有数字，遇到第一个比1大的数字，就交换这个数字和1的位置
	// 因为1后面的数字都可以确定是降序排列的，所以这次交换可以保证比1大的最小的一个数字会出现在1的位置上
	// 保证了下一个数字排列的正确性
	// 再将后续的3个数字的顺序倒置，保证后面3个数字的排列顺序是最小的原始的升序状态
	void NextPermutation(std::vector<int>& nums)
	{
		if (nums.size() == 0)
		{
			return;
		}

		for (int i = nums.size() - 2; i >= 0; --i)
		{
			if (nums[i] < nums[i + 1])
			{
				for (int j = nums.size() - 1; j > i; --j)
				{
					if (nums[j] > nums[i])
					{
						int temp = nums[j];
						nums[j] = nums[i];
						nums[i] = temp;
						std::reverse(nums.begin() + i + 1, nums.end());
						return;
					}
				}
			}
		}

		std::reverse(nums.begin(), nums.end());
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<int> vi = {1,4,3,2};
//	// 
//
//	s.NextPermutation(vi);
//
//	std::cout << vi[0] << vi[1] << vi[2] << vi[3] << std::endl;
//
//	return 0;
//}