#include <stdio.h>
#include <vector>
#include <string>

// https://leetcode-cn.com/problems/longest-common-prefix/

class Solution 
{
public:
	// 遍历纵向比较每一个字符串的字符，如果字符都相同，即存入结果中
	// 如果已达到某个字符串的末尾或者有任意一个字符不相同，即结束遍历，返回结果
	std::string LongestCommonPrefix(const std::vector<std::string>& strs)
	{
		if (strs.size() == 0)
		{
			return "";
		}

		std::string result;
		size_t length = strs[0].size();

		for (size_t i = 0; i < length; ++i)
		{
			char c = strs[0][i];
			for (size_t j = 1; j < strs.size(); ++j)
			{
				if (i >= strs[j].size() || strs[j][i] != c)
				{
					return result;
				}
			}

			result += c;
		}

		return result;
	}

	// 使用分治法，将大的问题分解为一个一个的小的问题，问题的最小规模为2个字符串求公共前缀
	// 小问题的结果将作为之前较大问题的条件参数回溯回去，从而得到最开始的最大问题的结果
	std::string LongestCommonPrefixDivideConquer(const std::vector<std::string>& strs)
	{
		if (strs.size() == 0)
		{
			return "";
		}

		return this->DivideConquer(strs, 0, strs.size() - 1);
	}

	// 使用二分查找的方法，首先找出字符串数组中最短的字符串，因为最大公共前缀的长度就是这个最短字符串的长度
	// 对这个最短字符串的长度做二分查找，分为左半部分和右半部分，然后对左半部分做遍历，看左半部分是否为一个公共前缀
	// 如果是公共前缀，保存部分结果，并将下次二分查找的区间定位到右半区，因为左半部分的公共前缀肯定是小于等于整个公共前缀的
	// 即右半部分可能还有公共前缀的一部分
	// 如果不是公共前缀，将下次二分查找的区间定位到左半区，公共前缀肯定存在于更靠左的位置
	// 持续进行二分查找，直到遍历结束，得出结果
	std::string LongestCommonPrefixBinarySearch(const std::vector<std::string>& strs)
	{
		if (strs.size() == 0)
		{
			return "";
		}

		int min_length = INT_MAX;
		int min_index = 0;
		for (size_t i = 0; i < strs.size(); ++i)
		{
			if (strs[i].size() < min_length)
			{
				min_length = strs[i].size();
				min_index = i;
			}
		}

		int left = 0;
		int right = min_length - 1;
		std::string result;

		while (left <= right)
		{
			int mid = (left + right) / 2;
			bool match = true;
			
			for (size_t i = 0; i < strs.size(); ++i)
			{
				for (int j = left; j <= mid; ++j)
				{
					if (strs[min_index][j] != strs[i][j])
					{
						match = false;
						break;
					}
				}

				if (!match)
				{
					break;
				}
			}

			if (match)
			{
				result += strs[min_index].substr(left, mid - left + 1);
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}

		return result;
	}

private:
	std::string DivideConquer(const std::vector<std::string>& strs, const int left, const int right)
	{
		if (right - left <= 1)
		{
			return this->CommonPrefix(strs[left], strs[right]);
		}

		int mid = (left + right) / 2;
		std::string left_result = this->DivideConquer(strs, left, mid);
		std::string right_result = this->DivideConquer(strs, mid + 1, right);

		return this->CommonPrefix(left_result, right_result);
	}

	std::string CommonPrefix(const std::string& str1, const std::string& str2)
	{
		std::string result;

		for (size_t i = 0; i < str1.size(); ++i)
		{
			char c = str1[i];

			if (i >= str2.size() || c != str2[i])
			{
				return result;
			}

			result += c;
		}

		return result;
	}
};

int main(int argc, char** argv)
{
	Solution s;

	std::vector<std::string> strs = { "flower","flow","flight" };

	std::string result = s.LongestCommonPrefixBinarySearch(strs);

	return 0;
}