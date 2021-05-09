#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

// https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/

class Solution
{
public:
	// words中的所有字符串都是等长的，所以当我们在s中寻找串联的子串的时候
	// 可以使用一个固定的步幅single_len来处理字符串
	// 我们使用一个map来保存words中所有字符出现的次数
	// total_len代表words中所有字符构成的子串的总长度
	// 遍历s字符串，以每个字符为起点，以single_len的长度获取每个字符
	// 使用临时的map来保存这些字符出现的次数，并且与之前的map中已保存的字符出现的次数进行对比
	// 如果个数相符，则找到合适的子串起始位置，如不相符，则继续下一次循环处理
	std::vector<int> FindSubString(const std::string& s, const std::vector<std::string>& words) 
	{
		std::vector<int> vi;
		
		if (s == "" || words.size() == 0)
		{
			return vi;
		}

		size_t single_len = words[0].size();
		size_t total_len = single_len * words.size();
		size_t s_len = s.size();
		std::unordered_map<std::string, int> words_map;

		for (size_t i = 0; i < words.size(); ++i)
		{
			words_map[words[i]] += 1;
		}

		for (size_t i = 0; i < s_len && s_len - i >= total_len; ++i)
		{
			bool flag = true;
			std::unordered_map<std::string, int> temp_words_map;
			for (size_t j = 0; j < words.size(); ++j)
			{
				std::string word = s.substr(i + j * single_len, single_len);
				if (temp_words_map[word] < words_map[word])
				{
					temp_words_map[word] += 1;
				}
				else
				{
					flag = false;
					break;
				}
			}

			if (flag)
			{
				vi.emplace_back(i);
			}
		}

		return vi;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::string str = "wordgoodgoodgoodbestword";
//	std::vector<std::string> vs = { "word", "good", "best", "word" };
//
//	std::vector<int> vi = s.FindSubString(str, vs);
//
//	return 0;
//}


