#include <iostream>
#include <vector>
#include <algorithm>

// https://leetcode-cn.com/problems/container-with-most-water/

class Solution 
{
public:
	// 从头尾分别向中心递进，假设一开始最大的面积是在头尾2个索引处
	// 由于高度是由短板来定义的，横向在一开始已经是最大了，所以之后为了寻找更大的面积
	// 只能缩小横向的宽度，寄希望于在纵向上有更高的高度
	// 由较低的那侧向高侧递进，来找到更高的高度，来弥补宽度减少的损失，从而获得更大的面积
	int MaxArea(const std::vector<int>& height)
	{
		if (height.size() == 0)
		{
			return 0;
		}

		int max_area = 0;
		int left = 0;
		int right = height.size() - 1;

		while (left < right)
		{
			int temp_area = std::min(height[left], height[right]) * (right - left);
			max_area = std::max(max_area, temp_area);

			if (height[left] < height[right])
			{
				++left;
			}
			else
			{
				--right;
			}
		}

		return max_area;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//	std::vector<int> vec = { 1, 8, 6, 2, 5, 4, 8, 3, 7 };
//
//	int max_area = s.MaxArea(vec);
//
//
//	return 0;
//}