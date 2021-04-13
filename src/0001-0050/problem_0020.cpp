#include <stdio.h>
#include <string>
#include <stack>

// https://leetcode-cn.com/problems/valid-parentheses/

class Solution 
{
public:
	// 由于这个题目中的括号不只包含小括号，还包括中括号和大括号
	// 所以如果单单使用几个变量来记录左括号的值，碰到右括号再使对应的变量-1
	// 这种方法是不适用的，因为没有考虑到三种括号位置的先后关系
	// 所以使用栈的方式来处理这种问题是最合适的，遍历字符串，遇到左括号入栈
	// 遇到右括号时查看栈顶元素，如果无元素或者不是对应的左括号则不是有效的括号结构
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