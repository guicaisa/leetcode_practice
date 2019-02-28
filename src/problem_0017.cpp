#include <stdio.h>
#include <string>
#include <vector>

/**
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 */

class Solution 
{
public:
	/**
	 * 求组合结果，使用递归处理
	 */
	std::vector<std::string> LetterCombinations(const std::string& digits)
	{
		std::vector<std::string> results;

		if (digits.size() == 0)
		{
			return results;
		}

		data_[2] = "abc";
		data_[3] = "def";
		data_[4] = "ghi";
		data_[5] = "jkl";
		data_[6] = "mno";
		data_[7] = "pqrs";
		data_[8] = "tuv";
		data_[9] = "wxyz";

		this->Combine(digits, 0, "", results);

		return results;
	}

private:
	void Combine(const std::string& digits, const uint32_t index, const std::string& combine_str, std::vector<std::string>& results)
	{
		int number = digits[index] - '0';

		for (size_t i = 0; i < data_[number].size(); ++i)
		{
			if (index == digits.size() - 1)
			{
				results.push_back(combine_str + data_[number][i]);
			}
			else
			{
				this->Combine(digits, index + 1, combine_str + data_[number][i], results);
			}
		}
	}

private:
	std::string data_[10];
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<std::string> results = s.LetterCombinations("23");
//
//
//	return 0;
//}