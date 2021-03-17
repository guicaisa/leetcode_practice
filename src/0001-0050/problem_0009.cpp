#include <stdio.h>
#include <vector>

// https://leetcode-cn.com/problems/palindrome-number/

class Solution
{
public:
	// 首先负数肯定不是回文数字，因为有一个负号
	// 然后个位数为0的数字除了0本身肯定也不是回文，因为没有前导的0
	// 剩下的情况我们使用反转的方式来处理
	// 反转数字的一半，每次遍历对10取模获得当前数字的个位数
	// 将其累加在反转的数字中，然后当前数字除以10，继续下次遍历
	// 当反转的数字大于或者等于当前数字的时候，表示已经正好反转了一半或者超出一半，停止遍历
	// 判断当前数字和反转是否相等(偶数对称情况)或者当前数字是否等于反转数字除以10(奇数对称情况)
	// 只反转一半的数字，而不是反转全部数字的方法，可以天然的不用处理数值溢出的情况。
	bool IsPalindrome(int x) 
	{
		if (x < 0 || (x % 10 == 0 && x != 0))
		{
			return false;
		}

		int half = 0;
		while (x > half)
		{
			half = half * 10 + x % 10;
			x /= 10;
		}

		return x == half || x == half / 10;
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