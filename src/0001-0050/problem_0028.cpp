#include <stdio.h>
#include <string>
#include <vector>

/**
 * https://leetcode.com/problems/implement-strstr/
 */

class Solution 
{
public:
	/**
	 * 暴力求解法，找到不同的字符的时候，将i的索引减去之前相同的长度
	 * 从不同的地方继续求解
	 */
	int StrStr(const std::string& haystack, const std::string& needle) 
	{
		if (needle == "")
		{
			return 0;
		}

		size_t j = 0;

		for (size_t i = 0; i < haystack.size(); ++i)
		{
			if (haystack[i] == needle[j])
			{
				++j;
				if (j == needle.size())
				{
					return i - j + 1;
				}
			}
			else
			{
				i -= j;
				j = 0;
			}
		}

		return -1;
	}

	/**
	 * kmp算法，根据已匹配的子串的最长前缀后缀长度，将i索引定位到合理的位置
	 * 即相同前后缀的第一位，继续进行判断，减少多余重复的判断
	 */
	int StrStrBetter(const std::string& haystack, const std::string& needle)
	{
		if (needle == "")
		{
			return 0;
		}

		std::vector<int> next(needle.size(), 0);

		this->GenerateKmpNext(needle, next);

		size_t j = 0;

		for (size_t i = 0; i < haystack.size(); ++i)
		{
			if (haystack[i] == needle[j])
			{
				++j;
				if (j == needle.size())
				{
					return i - j + 1;
				}
			}
			else
			{
				if (j > 0)
				{
					i -= (next[j - 1] + 1);
				}
				j = 0;
			}
		}

		return -1;
	}

private:
	/**
	 * kmp求解next数组，根据len的长度确定当前最长相同前后缀的长度
	 * 索引从下标1开始递进，根据len的长度和当前索引的值判断是否相同，将len的值增加
	 * 当遇到不同的字符的时候，代表不能继续匹配，需要根据len的值往前遍历
	 * 直到找到相同的值，以其对应的len为基础计算出当前子串的len
	 * 否则遍历结束，没找到，当前子串的len为0
	 */
	void GenerateKmpNext(const std::string& needle, std::vector<int>& next)
	{
		int len = 0;
		next[0] = 0;

		for (size_t i = 1; i < needle.size(); ++i)
		{
			while (len > 0 && needle[len] != needle[i])
			{
				len = next[len - 1];
			}

			if (needle[len] == needle[i])
			{
				++len;
			}

			next[i] = len;
		}
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	int ret = s.StrStrBetter("mississippi", "issip");
//
//
//	return 0;
//}