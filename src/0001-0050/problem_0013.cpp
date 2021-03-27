#include <stdio.h>
#include <string>
#include <unordered_map>

// https://leetcode-cn.com/problems/roman-to-integer/

class Solution
{
public:
	// 倒序遍历字符串，并保存前一个遍历的字符
	// 如果遇到数字1出现在对应的数字10或者5之前，需要减去对应的值
	// 用来处理4和9的特殊情况
	int RomanToInt(const std::string& s) 
	{
		std::unordered_map<char, int> roman_map;
		roman_map['I'] = 1;
		roman_map['V'] = 5;
		roman_map['X'] = 10;
		roman_map['L'] = 50;
		roman_map['C'] = 100;
		roman_map['D'] = 500;
		roman_map['M'] = 1000;

		int result = 0;
		char pre_char = 0;

		for (int i = s.size() - 1; i >= 0; --i)
		{
			int temp_value = roman_map[s[i]];
			if ((s[i] == 'I' && (pre_char == 'V' || pre_char == 'X')) ||
				(s[i] == 'X' && (pre_char == 'L' || pre_char == 'C')) ||
				(s[i] == 'C' && (pre_char == 'D' || pre_char == 'M')))
			{
				temp_value *= -1;
			}

			pre_char = s[i];
			result += temp_value;
		}

		return result;
	}

	// 简化代码
	int RomanToInt2(const std::string& s)
	{
		if (s == "")
		{
			return 0;
		}

		std::unordered_map<char, int> roman_map;
		roman_map['I'] = 1;
		roman_map['V'] = 5;
		roman_map['X'] = 10;
		roman_map['L'] = 50;
		roman_map['C'] = 100;
		roman_map['D'] = 500;
		roman_map['M'] = 1000;

		int result = roman_map[s.back()];
		for (int i = s.size() - 2; i >= 0; --i)
		{
			if (roman_map[s[i]] < roman_map[s[i + 1]])
			{
				result -= roman_map[s[i]];
			}
			else
			{
				result += roman_map[s[i]];
			}
		}

		return result;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	int result = s.RomanToInt("XII");
//
//	return 0;
//}