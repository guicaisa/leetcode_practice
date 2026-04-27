#include <string>
#include <stack>

using namespace std;

// https://leetcode.cn/problems/simplify-path/

class Solution 
{
public:
    //1. 栈
    //遍历字符串，通过索引记录的方式，将path按照斜杠/分割成一个个独立的子字符串
    //若子串为"."则直接跳过不入栈，若字串为".."并且栈不为空，则弹出栈顶元素，若为正常目录名则压入栈中
    //遍历完成之后，依次从栈中去元素，并且在每个目录名前补充/，若最终结果为空，则返回根目录/，否则返回拼接好的字符串
    string simplifyPath(string path) 
    {
        stack<string> ss;
        int index = -1;
        for (int i = 0; i < path.size(); ++i)
        {
            if (index == -1)
            {
                if (path[i] != '/')
                {
                    index = i;
                    if (i == path.size() - 1)
                    {
                        if (string str = path.substr(i, 1); str != ".")
                        {
                            ss.push(path.substr(i, 1));
                        }
                    }   
                }
            }
            else
            {
                if (path[i] == '/' || i == path.size() - 1)
                {
                    int length = i - index;
                    if (path[i] != '/')
                    {
                        ++length;
                    }
                    string str = path.substr(index, length);
                    if (str == "..")
                    {
                        if (!ss.empty())
                        {
                            ss.pop();
                        }
                    }
                    else if (str != ".")
                    {
                        ss.push(path.substr(index, length));
                    }
                    index = -1;
                }
            }
        }

        string result;
        int pre_cnt = 0;
        while (!ss.empty())
        {
            string str = ss.top();
            ss.pop();
            if (str == "")
            {
                continue;
            }
            result = "/" + str + result;
        }
        
        return result == "" ? "/" : result;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     string path = "/home/";
//     string result = s.simplifyPath(path);

//     path = "/home//foo/";
//     result = s.simplifyPath(path);

//     path = "/home/user/Documents/../Pictures";
//     result = s.simplifyPath(path);

//     path = "/../";
//     result = s.simplifyPath(path);

//     path = "/.../a/../b/c/../d/./";
//     result = s.simplifyPath(path);

//     path = "/.././GVzvE/./xBjU///../..///././//////T/../../.././zu/q/e";
//     result = s.simplifyPath(path);

//     path = "/.";
//     result = s.simplifyPath(path);

//     return 0;
// }