#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

// https://leetcode-cn.com/problems/combination-sum-ii/

class Solution 
{
public:
	// 由于每种组合中不能使用相同的数字，所以递归传参的时候，index必须为 i + 1
	// 去重操作体现在递归函数中，即每种相同的数字只进行一次的递归展开操作
	// 相同的部分全部跳过
	std::vector<std::vector<int> > CombinationSum2(std::vector<int>& candidates, const int target)
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
			if (i > 0 && candidates[i] == candidates[i - 1] && i > index)
			{
				continue;
			}

			temp.push_back(candidates[i]);
			Recursive(candidates, target - candidates[i], i + 1, temp, result);
			temp.pop_back();
		}
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<int> vi = { 2, 5, 2, 1, 2 };
//
//	std::vector<std::vector<int> > result = s.CombinationSum2(vi, 5);
//
//	return 0;
//}

