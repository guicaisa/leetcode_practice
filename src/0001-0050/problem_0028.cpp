#include <stdio.h>
#include <string>
#include <vector>

// https://leetcode-cn.com/problems/implement-strstr/

class Solution 
{
public:
	// 暴力求解法，逐个字符进行判断
	int StrStr(const std::string& haystack, const std::string& needle) 
	{
		if (needle.size() == 0)
		{
			return 0;
		}

		size_t size = haystack.size();
		size_t n_size = needle.size();

		for (size_t i = 0; i < size && size - i >= n_size; ++i)
		{
			if (haystack[i] == needle[0])
			{
				for (size_t j = i, k = 0; j < size && k < n_size; ++j, ++k)
				{
					if (haystack[j] == needle[k])
					{
						if (k == n_size - 1)
						{
							return i;
						}
					}
					else
					{
						break;
					}
				}
			}
		}

		return -1;
	}

	// kmp算法，根据已匹配的子串的最长前缀后缀长度，将i索引定位到合理的位置
	// 即相同前后缀的第一位，继续进行判断，减少多余重复的判断，提高效率
	// 在已匹配的字符串中，可能出现重复的部分比如在字符串"ABCDABEEFG"中查找字符串"ABCDABH"
	// 通过肉眼观察，我们会发现"ABCDABH"会在前6个字符与"ABCDABEEFG"的前6个字符匹配，为"ABCDAB"
	// 在第7个字符的时候产生了不匹配，这时候我们需要重新判断
	// 一般的做法是从"ABCDABEEFG"的第二个字符开始与"ABCDABH"继续进行匹配判断
	// 但是这种做法很浪费时间，得一个字符一个字符从头开始比较
	// 仔细观察第一次已匹配的子串"ABCDAB"中，首位各有2个"AB"，这就是这个子串的公共前缀和后缀
	// 由于这个子串是已匹配的，所以我们可以从他的公共前缀后缀部分开始下一次匹配判断，而不是继续依次递进一个字符再判断
	// 可以减少很多中间的流程，缩短算法的耗时，这个例子中就是从"ABCDABEEFG"的第二个A的位置开始进行第二次判断
	// 第一次匹配的时候索引为"ABCDABEEFG"中的0，第二次匹配根据已匹配的6个字符减去已匹配字符的公共前缀后缀长度2
	// 即第二次开始匹配的索引为"ABCDABEEFG"中的4的位置，就是第二个A的位置
	int StrStrKmp(const std::string& haystack, const std::string& needle)
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
	// kmp求解next数组，根据len的长度确定当前最长相同前后缀的长度
	// 索引从下标1开始递进，根据len的长度和当前索引的值判断是否相同，将len的值增加
	// 当遇到不同的字符的时候，代表不能继续匹配，需要根据len的值往前遍历
	// 直到找到相同的值，以其对应的len为基础计算出当前子串的len
	// 否则遍历结束，没找到，当前子串的len为0
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
//	int ret = s.StrStrKmp("mississippi", "ABCDABB");
//
//
//	return 0;
//}