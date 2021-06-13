#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

// https://leetcode-cn.com/problems/combination-sum/

class Solution 
{
public:
	// 递归回溯，遍历所有情况
	std::vector<std::vector<int> > CombinationSum(std::vector<int>& candidates, const int target) 
	{
		sort(candidates.begin(), candidates.end());
		std::vector<int> temp;
		std::vector<std::vector<int> > result;

		if (target == 0)
		{
			return result;
		}

		Recursive(candidates, target, 0, temp, result);

		return result;
	}

	void Recursive(const std::vector<int>& candidates, const int target, const int index, std::vector<int>& temp, 
		std::vector<std::vector<int> >& result)
	{
		if (target == 0)
		{
			result.push_back(temp);
		}

		for (int i = index; i < candidates.size() && target - candidates[i] >= 0; ++i)
		{
			temp.push_back(candidates[i]);
			Recursive(candidates, target - candidates[i], i, temp, result);
			temp.pop_back();
		}
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<int> vi = { 2, 3, 5 };
//
//	std::vector<std::vector<int> > result = s.CombinationSum(vi, 8);
//
//	return 0;
//}