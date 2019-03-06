#include <stdio.h>
#include <string>
#include <stack>

/**
 * https://leetcode.com/problems/valid-parentheses/
 */

class Solution 
{
public:
	/**
	 * 考虑括号的对称性结果，使用栈的方式，遇到左括号入栈
	 * 遇到右括号时查看栈顶元素，如果无元素或者不是对应的左括号则不是有效的括号结构
	 */
	bool IsValid(const std::string& s)
	{
		std::stack<char> char_st;

		for (size_t i = 0; i < s.size(); ++i)
		{
			switch (s[i])
			{
				case '(':
				case '[':
				case '{':
					char_st.push(s[i]);
					break;
				case ')':
					if (char_st.size() == 0 || char_st.top() != '(')
					{
						return false;
					}
					else
					{
						char_st.pop();
					}
					break;
				case ']':
					if (char_st.size() == 0 || char_st.top() != '[')
					{
						return false;
					}
					else
					{
						char_st.pop();
					}
					break;
				case '}':
					if (char_st.size() == 0 || char_st.top() != '{')
					{
						return false;
					}
					else
					{
						char_st.pop();
					}
					break;
				default:
					break;
			}
		}

		return char_st.size() == 0;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	bool ret = s.IsValid("{[]}");
//
//	return 0;
//}