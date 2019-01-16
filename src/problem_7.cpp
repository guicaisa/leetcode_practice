#include <stdio.h>
#include <vector>
#include <cmath>

/**
 * https://leetcode.com/problems/reverse-integer/
 */

class Solution
{
public:
	/**
	 * 逆转数字位数
	 */
	int Reverse(int x) 
	{
		int64_t result = 0;
		std::vector<int> digit_vec;

		while (x)
		{
			digit_vec.push_back(x % 10);
			x /= 10;
		}

		for (size_t i = 0; i < digit_vec.size(); ++i)
		{
			result += std::pow(10, digit_vec.size() - 1 - i) * digit_vec[i];
		}

		if (result > (std::pow(2, 31) - 1) || result < (-1 * std::pow(2, 31)))
		{
			return 0;
		}

		return result;
	}

	/**
	 * 优化代码，去除依赖数组和int64类型的操作
	 * 每遍历一次新的位数，就将原有结果乘10并加上新的余位
	 * 判断越界的方法为在每次计算出新值的时候提前判断
	 * 以正数举例，如果新result越界的话，那么旧result * 10 >= INT_MAX / 10，因为step永远只能是个位数
	 * 那么就只有两种情况
	 * 1. 旧result > INT_MAX / 10，那新result必然越界
	 * 2. 旧result == INT_MAX / 10，step > 7 必然越界
	 * 负数的情况同理
	 */
	int ReverseBetter(int x)
	{
		int result = 0;

		while (x)
		{
			int step = x % 10;

			if (result > INT_MAX / 10 || (result == INT_MAX / 10 && step > 7))
			{
				return 0;
			}

			if (result < INT_MIN / 10 || (result == INT_MIN / 10 && step < -8))
			{
				return 0;
			}

			result = result * 10 + (step);
			x /= 10;
		}

		return result;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//	int x = -2147483412;
//
//	int result = s.ReverseBetter(x);
//
//
//	return 0;
//}