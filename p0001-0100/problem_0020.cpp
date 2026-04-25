#include <string>
#include <stack>

// https://leetcode.cn/problems/valid-parentheses/

using namespace std;

class Solution 
{
public:
    //1. 栈
    //利用栈维护括号的匹配关系，遍历字符串，遇到左括号'('，'['，'{'时将其压入栈中
    //遇到右括号时，首先检查栈是否为空，若栈为空或栈顶元素不是对应的左括号，说明匹配失败，直接返回false
    //若匹配成功，弹出栈顶元素，继续遍历，遍历结束后，需检查栈是否为空，若栈内仍有残留元素，说明有左括号未被匹配，返回false，否则返回true
    bool isValid(string s) 
    {
        stack<char> st;
        for (int i = 0; i < s.size(); ++i)
        {
            switch (s[i])
            {
                case '(':
                case '[':
                case '{':
                    st.push(s[i]);
                    break;
                case ')':
                    if (st.empty() || st.top() != '(')
                    {
                        return false;
                    }
                    st.pop();
                    break;
                case ']':
                    if (st.empty() || st.top() != '[')
                    {
                        return false;
                    }
                    st.pop();
                    break;
                case '}':
                    if (st.empty() || st.top() != '{')
                    {
                        return false;
                    }
                    st.pop();
                    break;
            }
        }

        return st.empty();
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：s = "()"
//     //输出：true
//     string str = "()";
//     bool result = s.isValid(str);

//     //输入：s = "()[]{}"
//     //输出：true
//     str = "()[]{}";
//     result = s.isValid(str);

//     //输入：s = "(]"
//     //输出：false
//     str = "(]";
//     result = s.isValid(str);

//     //输入：s = "([])"
//     //输出：true
//     str = "([])";
//     result = s.isValid(str);

//     //输入：s = "([)]"
//     //输出：false
//     str = "([)]";
//     result = s.isValid(str);

//     return 0;
// }