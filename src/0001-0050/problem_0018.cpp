#include <stdio.h>
#include <vector>
#include <algorithm>

// https://leetcode-cn.com/problems/4sum/

class Solution 
{
public:
	// 切割问题，分离成为一个数字和一个三个数字，使用3Sum的方式求剩下的三个数字的结果
	std::vector<std::vector<int> > FourSum(std::vector<int>& nums, const int target) 
	{
		std::vector<std::vector<int> > results;
		sort(nums.begin(), nums.end());

		for (size_t i = 0; i < nums.size(); ++i)
		{
			if (nums.size() - i < 4)
			{
				break;
			}

			if (i > 0 && nums[i] == nums[i - 1])
			{
				continue;
			}

			this->ThreeSum(nums, i + 1, target - nums[i], results);
		}
	
		return results;
	}

private:
	void ThreeSum(const std::vector<int>& nums, const int start_index, const int target, std::vector<std::vector<int> >& results)
	{
		int first_num = nums[start_index - 1];

		for (size_t i = start_index; i < nums.size(); ++i)
		{
			if (nums.size() - i < 3)
			{
				break;
			}

			if (i > start_index && nums[i] == nums[i - 1])
			{
				continue;
			}

			int left = i + 1;
			int right = nums.size() - 1;

			while (left < right)
			{
				int sum = nums[i] + nums[left] + nums[right];
				if (sum < target)
				{
					++left;
				}
				else if (sum > target)
				{
					--right;
				}
				else
				{
					std::vector<int> temp_vec;
					temp_vec.emplace_back(first_num);
					temp_vec.emplace_back(nums[i]);
					temp_vec.emplace_back(nums[left]);
					temp_vec.emplace_back(nums[right]);
					results.push_back(temp_vec);

					while (left + 1 < nums.size() && nums[left] == nums[left + 1])
					{
						++left;
					}

					while (right > 0 && nums[right] == nums[right - 1])
					{
						--right;
					}

					++left;
					--right;
				}
			}
		}
	}
};

//
//int main(int argc, char** argv)
//{
//
//	Solution s;
//	std::vector<int> vec = { 1, 0, -1, 0, -2, 2 };
//
//	std::vector<std::vector<int> > ret = s.FourSum(vec, 0);
//
//
//	return 0;
//}