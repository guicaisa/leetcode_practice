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

	// 使用栈的方式，遍历的过程中将数组的索引入栈
	// 栈中的索引对应的值是递减的，所以当遍历到一个数大于栈顶索引对应的数时
	// 这表明出现了一个低洼处，此时弹出栈顶元素，作为当前需要计算的值
	// 此时如果栈中没有元素了，抛弃这个低洼，因为没有左边界无法积水
	// 如果栈中还有元素，可以称之为left，判断该索引对应的值和当前遍历到的值的大小
	// 较小的值减去当前计算的索引对应的值即为高度，left索引和当前遍历的索引之间的差即为宽
	// 宽乘高得到可以积水的数值累加到结果中
	int TrapStack(const std::vector<int>& height)
	{
		if (height.size() == 0)
		{
			return 0;
		}

		int sum = 0;
		std::stack<int> si;
		for (size_t i = 0; i < height.size(); ++i)
		{
			while (!si.empty() && height[i] > height[si.top()])
			{
				int top = si.top();
				si.pop();
				if (si.empty())
				{
					break;
				}
				int pre = si.top();
				int w = i - pre - 1;
				int h = std::min(height[i], height[pre]) - height[top];
				sum += w * h;
			}

			si.push(i);
		}

		return sum;
	}
	
	//使用双指针的方法，确定左右2个索引指针
	//遍历过程中，判断当前左右2个指针对应的值小，就从哪一侧计算
	//其实就是假设了一个边界，计算低的那一边(短板)
	//2个max变量用来记录遍历过程中，左右出现过的最大值
	//如果当前值比最大值大，肯定还没出现低洼，无法积水
	//如果当前值比最大值小，此刻低洼出现，同侧的一边有最大值
	//另一侧有比自己高的值，自己这个位置就形成了低洼
	//此时当前侧的最大值肯定比另一侧的边界值小，即短板
	//最大值减去当前所在位置值，即该位置的积水量，累计结果
	int TrapTwoPointers(const std::vector<int>& height)
	{
		if (height.size() == 0)
		{
			return 0;
		}

		int max_left = 0;
		int max_right = 0;
		int left = 0;
		int right = height.size() - 1;
		int sum = 0;
		while (left < right)
		{
			if (height[left] < height[right])
			{
				if (height[left] > max_left)
				{
					max_left = height[left];
				}
				else
				{
					sum += max_left - height[left];
				}
				++left;
			}
			else
			{
				if (height[right] > max_right)
				{
					max_right = height[right];
				}
				else
				{
					sum += max_right - height[right];
				}
				++right;
			}
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