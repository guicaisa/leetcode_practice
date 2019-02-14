#include <stdio.h>
#include <string>
#include <vector>

/**
 * https://leetcode.com/problems/regular-expression-matching/
 */

class Solution
{
public:
	/**
	 * '.'字符的情况很好处理，核心思想是如何处理'*'字符
	 * 因为匹配规则是'*'字符串可以代表0个或多个其之前的字符，所以有两种情况
	 * 1. 假设没有匹配0次，直接在匹配串pattern中跳过*和之前的字符
	 * 2. 有一个或多个匹配的字符，在原字符串text中继续往下判断是否匹配
	 * 使用递归回溯的方式，得到结果
	 */
	bool IsMatch(const std::string& s, const std::string& p)
	{
		if (p == "")
		{
			return s == "";
		}

		bool first_index_match_flag = s.size() > 0 && (s[0] == p[0] || p[0] == '.');

		if (p.size() >= 2 && p[1] == '*')
		{
			return this->IsMatch(s, p.substr(2)) || (first_index_match_flag && this->IsMatch(s.substr(1), p));
		}
		else
		{
			return first_index_match_flag && this->IsMatch(s.substr(1), p.substr(1));
		}
	}

	/**
	 * 使用动态规划的方式保存分段处理的结果，避免大量的字符串操作
	 * 具体方法和解决思路与上面的算法完全一致
	 */
	bool IsMatchBetter(const std::string& s, const std::string& p)
	{
		dp_results_.assign(s.size() + 1, std::vector<int>(p.size() + 1, -1));

		this->dp(0, 0, s, p);

		return dp_results_[0][0] == 1;
	}

private:
	bool dp(const size_t i, const size_t j, const std::string& s, const std::string& p)
	{
		if (dp_results_[i][j] != -1)
		{
			return dp_results_[i][j] == 1;
		}

		bool result = false;

		if (j == p.size())
		{
			result = i == s.size();
		}
		else
		{
			bool first_index_match_flag = i < s.size() && (s[i] == p[j] || p[j] == '.');

			if (j + 1 < p.size() && p[j + 1] == '*')
			{
				result = this->dp(i, j + 2, s, p) || (first_index_match_flag && this->dp(i + 1, j, s, p));
			}
			else
			{
				result = first_index_match_flag && this->dp(i + 1, j + 1, s, p);
			}
		}

		dp_results_[i][j] = result ? 1 : 0;

		return result;
	}

	std::vector<std::vector<int> > dp_results_;
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::string str = "aa";
//	std::string pattern = "a";
//
//	//"mississippi"
//	//"mis*is*ip*."
//
//	bool ret = s.IsMatchBetter(str, pattern);
//
//
//	return 0;
//}