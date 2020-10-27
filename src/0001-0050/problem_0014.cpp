#include <stdio.h>
#include <vector>
#include <string>

/**
 * https://leetcode.com/problems/longest-common-prefix/
 */

class Solution 
{
public:
	/**
	 * 找出最短的字符串，以其为基准判断所有字符串在垂直位置上同索引位置的字符，是否相同
	 */
	std::string LongestCommonPrefix(const std::vector<std::string>& strs)
	{
		if (strs.size() == 0)
		{
			return "";
		}

		std::string result;
		int min_size = INT_MAX;
		int min_index = 0;

		for (size_t i = 0; i < strs.size(); ++i)
		{
			if (strs[i].size() < min_size)
			{
				min_size = strs[i].size();
				min_index = i;
			}
		}

		for (size_t i = 0; i < strs[min_index].size(); ++i)
		{
			for (size_t j = 0; j < strs.size(); ++j)
			{
				if (strs[j][i] != strs[min_index][i])
				{
					return result;
				}
			}

			result += strs[min_index][i];
		}

		return result;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<std::string> strs;
//
//	std::string result = s.LongestCommonPrefix(strs);
//
//	return 0;
//}