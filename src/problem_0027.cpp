#include <stdio.h>
#include <vector>

/**
 * https://leetcode.com/problems/remove-element/
 */

class Solution 
{
public:
	int RemoveElement(std::vector<int>& nums, int val) 
	{
		int count = 0;
		std::vector<int> temp;

		for (size_t i = 0; i < nums.size(); ++i)
		{
			if (nums[i] != val)
			{
				++count;
				temp.push_back(nums[i]);
			}
		}

		nums = temp;

		return count;
	}

	/**
	 * 把不等于val的元素放在数组前面 
	 */
	int RemoveElementBetter(std::vector<int>& nums, int val)
	{
		size_t i = 0;

		for (size_t j = 0; j < nums.size(); ++j)
		{
			if (nums[j] != val)
			{
				nums[i] = nums[j];
				++i;
			}
		}

		return i;
	}
};

int main(int argc, char** argv)
{
	Solution s;
	std::vector<int> nums = { 3, 2, 2, 3 };

	int ret = s.RemoveElement(nums, 3);

	return 0;
}