#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string>

// https://leetcode-cn.com/problems/count-and-say/

class Solution 
{
public:
	// 找到规律，以"11"为例
	// 在生成下一个字符出的时候，根据已有字符串中的数字，如果有重复的比如'11'
	// 在下一个字符串中就变成'21'，如果只有一个'1'，就变成'11'，即在有相连的相同字符的情况下
	// 前面一个数字代表了已有字符的个数，如果只有一个的话，那前面只加1
	// 例如 '2211' 变成 '2221'，'2221' 变成 '3211'等
	std::string CountAndSay(const int n) 
	{
		if (n == 0)
		{
			return "";
		}

		std::string s = "1";

		for (int i = n - 1; i > 0; --i)
		{
			std::string t;
			for (int j = 0; j < s.size(); ++j)
			{
				int count = 1;
				for (int k = j + 1; k < s.size() && s[j] == s[k]; ++k, ++j, ++count)
				{
					;
				}

				char buf[100];
				sprintf(buf, "%d", count);

				t += buf + std::string(1, s[j]);
			}

			s = t;
		}

		return s;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::string t = s.CountAndSay(6);
//
//	return 0;
//}