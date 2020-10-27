#include <stdio.h>
#include <vector>
#include <map>

/**
 * https://leetcode.com/problems/next-permutation/
 */

class Solution
{
public:
	void NextPermutation(std::vector<int>& nums)
	{
		if (nums.size() == 0)
		{
			return;
		}

		std::map<int, int> greater;
		std::map<int, int> less;

		// 从后往前，找到第一个降序的数字，作为替换节点
		// 从该数字的后一个数字开始直到结尾，保存一部分大于其的数字和一部分小于其的数字
		// 并且将该部分的所有数字从数组中剔除
		// 从大于该数字的集合中找到最小的一个替换到该位置上去
		// 剩下的数字全部放在一个集合中，根据大小升序依次补位到原数组中
		for (int i = nums.size() - 1; i >= 1; --i)
		{
			if (nums[i] > nums[i - 1]) 
			{
				int t = nums[i - 1];
				for (int j = i; j < nums.size(); ++j)
				{
					if (nums[j] > t)
					{
						++greater[nums[j]];
					}
					else
					{
						++less[nums[j]];
					}
				}

				nums.erase(nums.begin() + i - 1, nums.end());

				nums.emplace_back(greater.begin()->first);
				if (--(greater.begin()->second) == 0)
				{
					greater.erase(greater.begin()->first);
				}
			
				++greater[t];
				for (std::map<int, int>::iterator it = less.begin(); it != less.end(); ++it)
				{
					greater[it->first] += it->second;
				}

				for (std::map<int, int>::iterator it = greater.begin(); it != greater.end(); ++it)
				{
					for (int j = 0; j < it->second; ++j)
					{
						nums.emplace_back(it->first);
					}
				}

				return;
			}
		}

		std::reverse(nums.begin(), nums.end());
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<int> vi = {1, 3, 2};
//	// 
//
//	s.NextPermutation(vi);
//
//	return 0;
//}