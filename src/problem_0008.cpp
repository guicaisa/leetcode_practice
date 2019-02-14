#include <stdio.h>
#include <vector>
#include <string>
#include <cctype>

/**
 * https://leetcode.com/problems/string-to-integer-atoi/
 */

class Solution
{
public:
	/**
	 * 遍历字符串，以遇到第一个数字字符或者'+'或者'-'为开端，之后如果遇到任何非数字字符，直接break
	 * 如果在这之前遇到其他无意义的字符，则直接返回0，最终获得一个数字数组，保存每一位的数字
	 * 遍历数组，每次进位，计算最终结果，在每次当前进位计算之前判断越界的可能
	 */
	int MyAtoi(const std::string& str) 
	{
		int character_flag = 0;
		bool positive = true;
		std::vector<int> digit_vec;

		for (size_t i = 0; i < str.size(); ++i)
		{
			if (character_flag == 0)
			{
				if (str[i] != ' ' && str[i] != '-' && str[i] != '+' && !isdigit(str[i]))
				{
					return 0;
				}

				if (str[i] != ' ')
				{
					character_flag = 1;
				}

				if (str[i] == '-')
				{
					positive = false;
				}
				else if (isdigit(str[i]))
				{
					digit_vec.emplace_back((str[i] - '0') * (positive ? 1 : -1));
				}
			}
			else
			{
				if (!isdigit(str[i]))
				{
					break;
				}

				digit_vec.emplace_back((str[i] - '0') * (positive ? 1 : -1));
			}
		}

		int result = 0;
		for (size_t i = 0; i < digit_vec.size(); ++i)
		{
			if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit_vec[i] > 7))
			{
				return INT_MAX;
			}
			
			if (result < INT_MIN / 10 || (result == INT_MIN / 10 && digit_vec[i] < -8))
			{
				return INT_MIN;
			}

			result = result * 10 + digit_vec[i];
		}

		return result;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//	std::string str = "42";
//
//	int ret = s.MyAtoi(str);
//
//
//	return 0;
//}