#include <stdio.h>
#include <cmath>

/**
 * https://leetcode.com/problems/divide-two-integers/
 */

class Solution 
{
public:
	/**
	 * 一直用被除数减去除数，直到小于除数为止，统计其次数，就是最后的商
	 * 一直循环减的话，效率太低，循环中套个循环，除数不断翻倍
	 * 扩大每步的计算范围，减少循环次数，提升效率
	 */
	int Divide(int dividend, int divisor)
	{
		if (dividend == INT_MIN && divisor == -1)
		{
			return INT_MAX;
		}

		bool symbol_flag = false;

		if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0))
		{
			symbol_flag = true;
		}

		long abs_dividend = labs(dividend);
		long abs_divisor = labs(divisor);
		long count = 0;

		while (abs_dividend >= abs_divisor)
		{
			long temp = abs_divisor;
			long num = 1;

			while ((temp << 1) <= abs_dividend)
			{
				temp <<= 1;
				num <<= 1;
			}

			abs_dividend -= temp;
			count += num;
		}

		return symbol_flag ? -1 * count : count;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	int ret = s.Divide(-2147483648, 1);
//
//
//	return 0;
//}