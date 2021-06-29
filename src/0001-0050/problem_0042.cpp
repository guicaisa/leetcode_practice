#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack>

// https://leetcode-cn.com/problems/trapping-rain-water/

class Solution 
{
public:
	// 暴力破解，对于每一个元素，分别从其位置向左右做两次遍历
	// 找到对应的left_max和right_max分别代表左边的最高值和右边的最高值
	// 由于积水是由短板决定，所以取min(left_max, right_max)
	// 该索引位置上能积水的数量为min(left_max, right_max) - height[i]
	// 依此遍历，累加结果
	int Trap(const std::vector<int>& height)
	{
		int sum = 0;

		for (int i = 1; i < int(height.size()) - 1; ++i)
		{
			int left_max = 0;
			int right_max = 0;

			for (int j = i; j >= 0; --j)
			{
				left_max = std::max(left_max, height[j]);
			}

			for (int j = i; j < height.size(); ++j)
			{
				right_max = std::max(right_max, height[j]);
			}
			
			sum += std::min(left_max, right_max) - height[i];
		}

		return sum;
	}

	// 暴力破解的方式效率太低，可以考虑使用动态规划的方式
	// 用额外数组的方式保存left_max和left_right，放在left_dp和right_dp中
	// left_dp[i]代表从i索引开始，左边的最大高度
	// right_dp[i]代表从i索引开始，右边的最大高度
	// 分别左右遍历各一次，填充2个dp数组
	// 遍历数组，根据左右数组中的最高值小的一方为基准(木桶短板)
	// 获得与当前位置高度的差值，累计到结果中
	int TrapDp(const std::vector<int>& height)
	{
		if (height.size() == 0)
		{
			return 0;
		}

		std::vector<int> left(height.size(), 0);
		std::vector<int> right(height.size(), 0);

		left[0] = height[0];
		right[height.size() - 1] = height[height.size() - 1];

		for (int i = 1; i < height.size(); ++i)
		{
			left[i] = height[i] > left[i - 1] ? height[i] : left[i - 1];
		}

		for (int i = height.size() - 2; i >= 0; --i)
		{
			right[i] = height[i] > right[i + 1] ? height[i] : right[i + 1];
		}

		int sum = 0;

		for (int i = 1; i < height.size() - 1; ++i)
		{
			sum += (left[i] < right[i] ? left[i] : right[i]) - height[i];
		}

		return sum;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<int> vi = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
//
//	int ret = s.Trap(vi);
//
//	return 0;
//}