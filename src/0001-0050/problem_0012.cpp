#include <stdio.h>
#include <string>
#include <unordered_map>

/**
 * https://leetcode.com/problems/integer-to-roman/
 */

class Solution
{
public:
	/**
	 * 单独处理4，5，9三个数字，少于5的数字和大于5的数字有统一的处理方式
	 */
	std::string IntToRoman(int num)
	{
		std::unordered_map<int, std::unordered_map<std::string, char> > roman_map;
		roman_map[1]["1"] = 'I';
		roman_map[1]["5"] = 'V';
		roman_map[2]["1"] = 'X';
		roman_map[2]["5"] = 'L';
		roman_map[3]["1"] = 'C';
		roman_map[3]["5"] = 'D';
		roman_map[4]["1"] = 'M';

		int step = 1;
		std::string result;

		while (num)
		{
			int step_num = num % 10;
			std::string temp_str;

			switch (step_num)
			{
				case 4:
					temp_str = std::string(1, roman_map[step]["1"]) + std::string(1, roman_map[step]["5"]);
					break;
				case 5:
					temp_str = std::string(1, roman_map[step]["5"]);
					break;
				case 9:
					temp_str = std::string(1, roman_map[step]["1"]) + std::string(1, roman_map[step + 1]["1"]);
					break;
				default:
					if (step_num < 5)
					{
						temp_str = std::string(step_num, roman_map[step]["1"]);
					}
					else if (step_num > 5)
					{
						temp_str = std::string(1, roman_map[step]["5"]) + std::string(step_num - 5, roman_map[step]["1"]);
					}
					break;
			}

			result = temp_str + result;
			num /= 10;
			++step;
		}

		return result;
	}

	/**
	 * 减少耗时
	 */
	std::string IntToRomanFaster(int num)
	{
		int step = 1;
		std::string result;

		while (num)
		{
			int step_num = num % 10;
			std::string temp_str;

			if (step == 1)
			{
				switch (step_num)
				{
					case 9:
						temp_str = "IX";
						break;
					case 4:
						temp_str = "IV";
						break;
					case 5:
						temp_str = "V";
						break;
					default:
						if (step_num > 5)
						{
							temp_str = "V" + std::string(step_num - 5, 'I');
						}
						else if (step_num < 5)
						{
							temp_str = std::string(step_num, 'I');
						}
						break;
				}
			}
			else if (step == 2)
			{
				switch (step_num)
				{
					case 9:
						temp_str = "XC";
						break;
					case 4:
						temp_str = "XL";
						break;
					case 5:
						temp_str = "L";
						break;
					default:
						if (step_num > 5)
						{
							temp_str = "L" + std::string(step_num - 5, 'X');
						}
						else if (step_num < 5)
						{
							temp_str = std::string(step_num, 'X');
						}
						break;
				}
			}
			else if (step == 3)
			{
				switch (step_num)
				{
					case 9:
						temp_str = "CM";
						break;
					case 4:
						temp_str = "CD";
						break;
					case 5:
						temp_str = "D";
						break;
					default:
						if (step_num > 5)
						{
							temp_str = "D" + std::string(step_num - 5, 'C');
						}
						else if (step_num < 5)
						{
							temp_str = std::string(step_num, 'C');
						}
						break;
					}
			}
			else if (step == 4)
			{
				temp_str = std::string(step_num, 'M');
			}

			result = temp_str + result;
			num /= 10;
			++step;
		}

		return result;
	}

};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::string str = s.IntToRomanFaster(1994);
//
//	return 0;
//}