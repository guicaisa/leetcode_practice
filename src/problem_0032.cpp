#include <stdio.h>
#include <string>
#include <vector>
#include <stack>
#include <map>

/**
 * https://leetcode.com/problems/longest-valid-parentheses/
 */

class Solution {
public:
	// 动态规划 dp数组中dp[i]代表s[0...i]的字串中最长的有效括号长度
	// 根据括号的特性，有2种情况
	// 1. 当s[i] == ')' 并且 s[i - 1] == '('时，s[i-1...i]之间的有效括号长度为2
	// 此时判断s[0...s-2]之间的有效括号长度，即dp[i - 2]，在此基础上+2，即得到公式
	// dp[i] = dp[i - 2] + 2
	// 2. 当s[i] == ')' 并且 s[i - 1] == ')'时，向前寻找对应的'('和最后一个s[i]的')'匹配
	// 这种情况只能成立在前面的'('与最后的')'之间的子串是有效括号才行，所以根据s[i - 1]对应的dp[i - 1]
	// 得到有效括号长度后，向前寻找这串子串之前的一个字符是否为'('，即s[i - dp[i - 1] - 1] == '('
	// 如果成立，即s[i - dp[i - 1] - 1] 到 s[i]之间都是有效的括号，此时dp[i] = dp[i - 1] + 2
	// 但是如果在s[i - dp[i - 1] - 1]之前，还有有效的括号子串的话，就需要再加上这部分的长度
	// 即最终dp[i] = dp[i - dp[i - 1] - 2] + dp[i - 1] + 2
	int LongestValidParentheses(const std::string& s) 
	{
		if (s == "")
		{
			return 0;
		}

		int max_len = 0;
		std::vector<int> dp = std::vector<int>(s.size(), 0);

		for (int i = 1; i < s.size(); ++i)
		{
			if (s[i] == '(')
			{
				dp[i] = 0;
			}
			else if (s[i] == ')' && s[i - 1] == '(')
			{
				dp[i] = i - 2 >= 0 ? dp[i - 2] + 2 : 2;
			}
			else if (s[i] == ')' && s[i - 1] == ')' && (i - dp[i - 1] - 1) >= 0 && s[i - dp[i - 1] - 1] == '(')
			{
				dp[i] = i - dp[i - 1] - 2 >= 0 ? dp[i - dp[i - 1] - 2] + dp[i - 1] + 2 : dp[i - 1] + 2;
			}

			if (dp[i] > max_len)
			{
				max_len = dp[i];
			}
		}

		return max_len;
	}

	// 栈的方法
	// 保持栈底一直有一个标识起始位置索引的值，'('入栈，')'出栈
	// 出栈时根据该索引计算有效括号的长度
	int LongestValidParenthesesStack(const std::string& s)
	{
		int max_len = 0;
		std::stack<int> st;
		st.push(-1);

		for (int i = 0; i < s.size(); ++i)
		{
			if (s[i] == '(')
			{
				st.push(i);
			}
			else if (s[i] == ')')
			{
				if (st.empty())
				{
					st.push(i);
				}
				else
				{
					st.pop();
					if (st.empty())
					{
						st.push(i);
					}
					else
					{
						int offset = i - st.top();
						max_len = offset > max_len ? offset : max_len;
					}
				}
			}
		}

		return max_len;
	}

	// 左右遍历，根据'('和')'出现配对的情况进行判断
	int LongestValidParenthesesThrough(const std::string& s)
	{
		int max_len = 0;
		int left_count = 0;
		int right_count = 0;

		for (int i = 0; i < s.size(); ++i)
		{
			if (s[i] == '(')
			{
				++left_count;
			}
			else if (s[i] == ')')
			{
				++right_count;
			}

			if (left_count == right_count)
			{
				max_len = left_count + right_count > max_len ? left_count + right_count : max_len;
			}
			else if (right_count > left_count)
			{
				left_count = 0;
				right_count = 0;
			}
		}

		left_count = 0;
		right_count = 0;

		for (int i = s.size() - 1; i >= 0; --i)
		{
			if (s[i] == '(')
			{
				++left_count;
			}
			else if (s[i] == ')')
			{
				++right_count;
			}

			if (left_count == right_count)
			{
				max_len = left_count + right_count > max_len ? left_count + right_count : max_len;
			}
			else if (left_count > right_count)
			{
				left_count = 0;
				right_count = 0;
			}
		}
		
		return max_len;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::string ss = "())((())";
//
//	int ret = s.LongestValidParenthesesStack(ss);
//
//
//	return 0;
//}
















