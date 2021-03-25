#include <stdio.h>
#include <string>
#include <unordered_map>

// https://leetcode-cn.com/problems/integer-to-roman/

class Solution
{
public:
	// 单独处理4，5，9三个数字
	// 小于4和大于5的数字，有统一的处理方式
	// 数字1-3根据个数使用对应的数字1累加
	// 数字6-8根据个数在对应的数字5后面加上对应个数的1
	// 额外的我们需要根据当前的个，十，百，千的位数来选择对应的罗马数字
	std::string IntToRoman(int num)
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

	// 排列出数字和罗马字符对应的数组，特别列出4和9相关数字对应的字符
	// 输入数字不断减去对应的数字，并将相应的罗马字符添加到结果中
	// 已处理好4和9的情况，剩余的2，3，6，7，8只需要用相应的数字1来堆积就可以了
	std::string IntToRoman2(int num)
	{
		std::string result;
		std::vector<int> vi = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
		std::vector<std::string> vr = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

		for (size_t i = 0; i < vi.size(); ++i)
		{
			while (num >= vi[i])
			{
				num -= vi[i];
				result += vr[i];
			}
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