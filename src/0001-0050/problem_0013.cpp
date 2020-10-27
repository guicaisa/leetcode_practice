#include <stdio.h>
#include <string>
#include <unordered_map>

/**
 * https://leetcode.com/problems/roman-to-integer/
 */

class Solution
{
public:
	/**
	 * 六种特殊情况，需要减对应的数字
	 * IV，IX，XL，XC，CD，CM
	 */
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
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	int result = s.RomanToInt("XII");
//
//	return 0;
//}