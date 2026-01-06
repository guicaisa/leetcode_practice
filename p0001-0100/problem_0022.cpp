#include <vector>
#include <string>
#include <stack>

// https://leetcode.cn/problems/generate-parentheses/

using namespace std;

class Solution 
{
public:
    vector<string> generateParenthesis(int n) 
    {
        if (n <= 0)
        {
            return vector<string>();
        }

        string str;
        vector<string> results;
        stack<int> st;
        this->recursive(n, st, str, results);
        return results;
    }

    void recursive(int n, stack<int> st, string& str, vector<string>& results)
    {
        if (n == 0 && st.size() == 0)
        {
            results.push_back(str);
            return;
        }
        if (st.size() == 0 || n > 0)
        {
            st.push(1);
            str += '(';
            this->recursive(n-1, st, str, results);
            st.pop();
            str = str.substr(0, str.size() - 1);
        }
        
        if (st.size() > 0)
        {
            st.pop();
            str += ')';
            this->recursive(n, st, str, results);
            st.push(1);
            str = str.substr(0, str.size() - 1);
        }
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: n = 3   
//     //输出: ["((()))","(()())","(())()","()(())","()()()"]
//     vector<string> results = s.generateParenthesis(3);

//     //输入: n = 1
//     //输出: ["()"]
//    results = s.generateParenthesis(1);

//     return 0;
// }