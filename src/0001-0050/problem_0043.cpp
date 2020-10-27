#include <stdio.h>
#include <stdlib.h>
#include <string>

/**
 * https://leetcode.com/problems/multiply-strings/
 */

class Solution {
public:
	// 使用乘法计算的方式，根据数字所在的位置，推算其乘积所在的位置
	// 并且根据计算结果，向前进位
	std::string Multiply(const std::string& num1, const std::string& num2) {
		std::string result(num1.size() + num2.size(), '0');

		for (int i = num1.size() - 1; i >= 0; --i) {
			for (int j = num2.size() - 1; j >= 0; --j) {
				int temp = (num1[i] - '0') * (num2[j] - '0') + (result[i + j + 1] - '0');

				result[i + j + 1] = temp % 10 + '0';
				result[i + j] += temp / 10;
			}
		}

		std::size_t pos = result.find_first_not_of('0');
		if (pos != std::string::npos) {
			return result.substr(pos);
		}

		return "0";
	}
};

//int main(int argc, char** argv) {
//	Solution s;
//
//	std::string ret = s.Multiply("123", "456");
//
//
//	return 0;
//}