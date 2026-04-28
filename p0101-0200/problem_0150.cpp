#include <vector>
#include <string>
#include <stack>

// https://leetcode.cn/problems/evaluate-reverse-polish-notation/

using namespace std;

class Solution 
{
public:
    //1. 栈
    //序遍历tokens，若当前元素为数字，则将其压入栈
    //若当前元素为运算符，从栈中依次弹出两个元素，分别作为右操作数和左操作数(注意顺序)进行运算
    //将运算结果再次压入栈中，遍历结束后，栈内唯一的元素即为表达式的最终结果
    int evalRPN(vector<string>& tokens) 
    {
        if (tokens.size() == 0)
        {
            return 0;
        }

        stack<int> st;
        for (int i = 0; i < tokens.size(); ++i)
        {
            string str = tokens[i];
            if (!isOperator(str))
            {
                st.push(atoi(str.c_str()));
                continue;
            }
            int result = 0;
            int right = st.top();
            st.pop();
            int left = st.top();
            st.pop();
            switch (str[0])
            {
                case '+':
                    result = left + right;
                break;
                case '-':
                    result = left - right;
                break;
                case '*':
                    result = left * right;
                break;
                case '/':
                    result = left / right;
                break;
            }
            st.push(result);
        }
        
        return st.top();
    }

    bool isOperator(const string& str)
    {
        return str == "+" || str == "-" || str == "*" || str == "/";
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：tokens = ["2","1","+","3","*"]
//     //输出：9
//     vector<string> tokens = {"2", "1", "+", "3", "*"};
//     int result = s.evalRPN(tokens);

//     //输入：tokens = ["4","13","5","/","+"]
//     //输出：6
//     tokens = {"4", "13", "5", "/", "+"};
//     result = s.evalRPN(tokens);

//     //输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
//     //输出：22
//     tokens = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
//     result = s.evalRPN(tokens);

//     return 0;
// }