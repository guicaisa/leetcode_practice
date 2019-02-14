#include <stdio.h>
#include <vector>

/**
 * https://leetcode.com/problems/palindrome-number/
 */

class Solution
{
public:
	/**
	 * 使用数组把每个数字存储起来，再从头尾分别对比
	 */
	bool IsPalindrome(int x) 
	{
		if (x < 0)
		{
			return false;
		}

		std::vector<int> digit_vec;

		do
		{
			digit_vec.emplace_back(x % 10);
			x /= 10;
		} while (x);

		size_t size = digit_vec.size();

		for (size_t i = 0; i < size; ++i)
		{
			if (digit_vec[i] != digit_vec[size - i - 1])
			{
				return false;
			}
		}

		return true;
	}

	/**
	 * 更简单明了的方法，直接翻转该数字，然后与原数字比较
	 */
	bool IsPalindromeBetter(int x)
	{
		if (x < 0)
		{
			return false;
		}

		int reverse_num = 0;
		int temp = x;
		
		do
		{
			reverse_num = reverse_num * 10 + temp % 10;
			temp /= 10;
		} while (temp);

		return reverse_num == x;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	bool ret = s.IsPalindromeBetter(121);
//
//	return 0;
//}