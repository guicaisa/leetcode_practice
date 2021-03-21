#include <stdio.h>
#include <string>
#include <vector>

// https://leetcode-cn.com/problems/regular-expression-matching/

class Solution
{
public:
	// 普通字符和'.'字符的情况很好处理，核心思想是如何处理'*'字符
	// 因为匹配规则是'*'字符串可以代表0个或多个其之前的字符，所以需要处理三种情况
	// 1. 假设'*'和其之前的字符不匹配s中的任何字符，直接在匹配串pattern中跳过*和之前的字符
	// 继续判断pattern剩余中的字符与s是否匹配，被跳过的'*'和其之前的字符肯定是符合匹配的
	// 2. 假设'*'和之前的字符在s中有一个匹配的字符，则pattern保持不动，在s中继续往下判断是否匹配
	// 3. 假设pattern中的前2个字符中不包含'*'，则pattern和s做正常的1对1相等判断，然后同时往下进位，继续判断
	// 这种情况，整体的结果需要依赖多种分支情况后的子问题的结果来判断，所以非常适合使用递归回溯
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

	// 使用动态规划的方式保存分支处理的结果，避免大量的字符串复制操作
	// dp[i][j]代表s中从索引i开始到结尾的子串和pattern中从索引j开始到结尾的子串是否匹配
	// 我们从上面的递归回溯的算法中得到了启发，可以推导出相应的状态转移公式
	// 首先假设s的长度为m，pattern的长度为n，构建二维数组dp，行数为m+1，列数为n+1
	// m和n分别加1是为了优雅的处理边界情况。在经过准备工作之后，我们分析出以下四种情况
	// 1. j == n，即pattern已经遍历结束，此时的dp[i][j]的结果取决于s是否遍历完，即i是否等于m
	// 如果s还没遍历完，还有字符剩余，但是pattern已经没字符了，肯定不匹配
	// 2. j + 1 < n && p[j + 1] == '*' 即pattern还没遍历完，并且至少还有2个字符存在，并且第二个字符为'*'
	// 此时我们假设p[j]这个字符和后面的'*'组成的匹配串不匹配任何字符，那dp[i][j] = dp[i][j + 2]
	// 即越过pattern串中的2个字符，继续判断后续的内容
	// 3. j + 1 < n && p[j + 1] == '*' 即pattern还没遍历完，并且至少还有2个字符存在，并且第二个字符为'*'
	// 此时我们假设s[i] == p[j] || p[j] == '.'，表示pattern中的p[j] + '*'匹配了当前s中的一个字符
	// 那dp[i][j] = (s[i] == p[j] || p[j] == '.') && dp[i + 1][j]，我们保持pattern不动，由s继续往后遍历再进行判断
	// 4. j + 1 >= n || p[j + 1] != '*'，即表示当前的pattern已经到了最后一个字符，或者当前字符的后一个字符不为'*'
	// 此时dp[i][j] = (s[i] == p[j] || p[j] == '.') && dp[i + 1][j + 1]，s和pattern中的当前字符相等，2个子串同步往后继续判断后面的内容
	// 注意构建dp数组的时候得从后往前，因为前面的结果依赖后面子串的结果。
	bool IsMatchDp(const std::string& s, const std::string& p)
	{
		if (p == "")
		{
			return s == "";
		}

		int m = s.size();
		int n = p.size();
		std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, -1));
		
		for (int i = m; i >= 0; --i)
		{
			for (int j = n; j >= 0; --j)
			{
				if (j == n)
				{
					dp[i][j] = i == m;
					continue;
				}

				bool first_index_match_flag = i < m && (s[i] == p[j] || p[j] == '.');

				if (j + 1 < n && p[j + 1] == '*')
				{
					dp[i][j] = dp[i][j + 2] || (first_index_match_flag && dp[i + 1][j]);
				}
				else
				{
					dp[i][j] = first_index_match_flag && dp[i + 1][j + 1];
				}
			}
		}

		return dp[0][0];
	}

	// 同样是动态规划，但是这个算法使用从前往后构建dp数组
	// dp[i][j]表示s从0到索引i处的子串和p从0到索引j处的子串是否匹配
	// 与第一种动态规划方式一样，m和n分别为s和p的长度，dp数组的行和列为m+1，n+1
	// 这里+1也是为了处理边界问题。同样的，我们分析出四种情况
	// 1. j == 0，p还没有开始遍历，dp[i][j] = i == 0，结果取决于i是否等于0
	// 2. j >= 2 && p[j - 1] == '*'，p中已经至少有2个字符，并且当前这个字符为'*'
	// 注意这里我们使用的是p[j - 1]，因为在初始准备部分dp的行和列都+1，所以dp中的i和j对应实际s和p中的索引需要-1
	// dp中的i和j等于0代表s和p还没开始遍历的情况。这里我们假设'*'和其之前的字符匹配0次，那么直接跳过这2个字符
	// dp[i][j] = dp[i][j - 2]，当前的状态需要依赖之前的结果
	// 3. j >= 2 && p[j - 1] == '*'，p中已经至少有2个字符，并且当前这个字符为'*'
	// 此时我们假设s中的当前字符与p中的'*'和其之前的字符匹配，那么p不动，s继续往前判断
	// dp[i][j] = dp[i - 1][j]
	// 4. j < 2 || p[j - 1] != '*'，p中字符数少于2个或者当前字符不是'*'，只能进行字符1对1的单独判断
	// 假设当前2个字符匹配，那么就需要寻找s和p之前的状态，dp[i][j] = dp[i - 1][j - 1]
	// 我们从头开始遍历，后面的结果依赖前面的计算结果，最终dp[m][n]为最终的答案
	// 注意一个细节，这种从头遍历的方式和从尾遍历的方式，有一个不同之处
	// 在判断p中'*'字符与其之前的字符是否匹配s中的一个当前字符时，从头遍历的方式，由于dp的定义是从0到索引的子串
	// 状态转移是从前往后，所以后面的结果依赖前面的结果，如果p中当前字符是'*'的话，得判断'*'前面的字符是否与s中的当前字符匹配
	// 不然会漏掉一个结果分支，从尾遍历的方式则不需要，因为其状态转移是从后往前，前面的结果依赖后面的结果
	// 只需要单独判断当前2个字符即可
	bool IsMatchDpLeftToRight(const std::string& s, const std::string& p)
	{
		if (p == "")
		{
			return s == "";
		}

		int m = s.size();
		int n = p.size();
		std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, -1));

		for (int i = 0; i < m + 1; ++i)
		{
			for (int j = 0; j < n + 1; ++j)
			{
				if (j == 0)
				{
					dp[i][j] = i == 0;
					continue;
				}

				int si = i - 1;
				int pj = j - 1;

				bool last_index_match_flag = i >= 1 && (s[si] == p[pj] || p[pj] == '.' || 
					(pj > 0 && p[pj] == '*' && (p[pj - 1] == s[si] || p[pj - 1] == '.')));

				if (j >= 2 && p[pj] == '*')
				{
					dp[i][j] = dp[i][j - 2] || last_index_match_flag && dp[i - 1][j];
				}
				else
				{
					dp[i][j] = last_index_match_flag && dp[i - 1][j - 1];
				}
			}
		}

		return dp[m][n];
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	/*std::string str = "aac";
//	std::string pattern = ".*";*/
//
//	std::string str = "ba";
//	std::string pattern = ".c";
//
//	//"mississippi"
//	//"mis*is*ip*."
//
//	bool ret = s.IsMatchDpLeftToRight(str, pattern);
//
//
//	return 0;
//}