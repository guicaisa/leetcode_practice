#include <stdio.h>
#include <string>
#include <vector>
#include <stack>

// https://leetcode-cn.com/problems/generate-parentheses/

class Solution {
public:
	//使用递归回溯的方式，获得每一种括号结果
	//注意，右括号必须保证在已经有左括号的前提下，才可以进行递归求解，不然不是有效的括号组合
	//所以在递归左括号的时候，给right_num + 1，表明可使用的右括号+1
	std::vector<std::string> GenerateParenthesis(const int n)
	{
		std::vector<std::string> results;

		this->Recursive(n, 0, "", results);

		return results;
	}

private:
	void Recursive(const int left_num, const int right_num, const std::string& str, std::vector<std::string>& results)
	{
		if (left_num > 0)
		{
			this->Recursive(left_num - 1, right_num + 1, str + '(', results);
		}

		if (right_num > 0)
		{
			this->Recursive(left_num, right_num - 1, str + ')', results);
		}

		if (left_num == 0 && right_num == 0)
		{
			if (str != "")
			{
				results.push_back(str);
			}
		}
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<std::string> ret = s.GenerateParenthesis(3);
//
//	return 0;
//}