#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/**
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 */

class Solution
{
public:
	/**
	 * 暴力求解，遍历所有可能出现的子串，低效
	 */
	int LengthOfLongestSubstring(const std::string& s)
	{
		if (s == "")
		{
			return 0;
		}

		std::unordered_map<char, int> char_to_index;
		int max_length = 1;

		for (size_t i = 0; i < s.size(); )
		{
			if (char_to_index.find(s[i]) == char_to_index.end())
			{
				char_to_index[s[i]] = i;
				++i;

				if (i == s.size())
				{
					max_length = char_to_index.size() > max_length ? char_to_index.size() : max_length;
				}
			}
			else
			{
				if (char_to_index.size() > 1)
				{
					max_length = char_to_index.size() > max_length ? char_to_index.size() : max_length;
					i = char_to_index[s[i]] + 1;
					char_to_index.clear();
				}
				else
				{
					char_to_index[s[i]] = i;
					++i;
				}
			}
		}

		return max_length;
	}

	/**
	 * 使用滑动窗口维持一个不包含重复字符的字串的索引集合
	 * 往右扩展遇到不重复的字符就就行添加，碰到重复的字符，将左侧边界不停右移，直到去除重复字符为止
	 */
	int LengthOfLongestSubstringBetter(const std::string& s)
	{
		std::unordered_set<int> char_set;
		int max_length = 0;

		for (size_t i = 0, j = 0; i < s.size() && j < s.size(); )
		{
			if (char_set.find(s[j]) == char_set.end())
			{
				char_set.insert(s[j++]);
				max_length = char_set.size() > max_length ? char_set.size() : max_length;
			}
			else
			{
				char_set.erase(s[i++]);
			}
		}

		return max_length;
	}

	/**
	 * 滑动窗口的更简易方式，在向右扩展碰到重复字符时
	 * 直接将左侧拉到该字符上一次出现的位置之后，省去多步操作
	 * 对于"abba"这样的测试用例，在遇到重复的b时，左侧的i索引已经更新到第二个b所在的位置
	 * 所以在结尾遇到第二个a的时候，由于之前出现的a的索引小于i，所以不予考虑
	 */
	int LengthOfLongestSubstringBetter2(const std::string& s)
	{
		std::unordered_map<char, int> char_to_index;
		int max_length = 0;

		for (size_t i = 0, j = 0; i < s.size() && j < s.size(); ++j)
		{
			if (char_to_index.find(s[j]) != char_to_index.end())
			{
				i = char_to_index[s[j]] + 1 > i ? char_to_index[s[j]] + 1 : i;
			}

			char_to_index[s[j]] = j;
			max_length = j - i + 1 > max_length ? j - i + 1 : max_length;
		}

		return max_length;
	}

	/**
	 * 原理与滑动窗口相同，也是在遇到重复字符的时候，将左边界移动到上次出现该字符的位置
	 * 由于ASCII只有256位，使用256维度的数组代替哈希表，更加简化
	 */
	int LengthOfLongestSubstringBetter3(const std::string& s)
	{
		std::vector<int> char_to_index(256, -1);
		int start = -1;
		int max_length = 0;

		for (size_t i = 0; i < s.size(); ++i)
		{
			if (char_to_index[s[i]] > start)
			{
				start = char_to_index[s[i]];
			}

			max_length = i - start > max_length ? i - start : max_length;
			char_to_index[s[i]] = i;
		}

		return max_length;
	}
	
};

//int main(int argc, char** argv)
//{
//	Solution s;
//	std::string str = "abba";
//
//	int len = s.LengthOfLongestSubstringBetter2(str);
//
//
//	return 0;
//}