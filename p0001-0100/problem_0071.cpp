#include <string>
#include <stack>

using namespace std;

// https://leetcode.cn/problems/simplify-path/

class Solution 
{
public:
    //1. 栈
    //遍历字符串，将被斜杠划分出的字符串添加到栈中
    //遍历完成之后，开始不断从栈中弹出元素，如果是"."或者空字符串就略过
    //如果是".."就记录次数，遇到其他正常的元素就拼接到结果字符串中
    //如果之前只记录".."次数的话，在遇到正常字符串的时候，就不进行拼接，用掉次数并略过
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
                        ss.push(path.substr(i, 1));
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
                    ss.push(path.substr(index, length));
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
            if (str == "" || str == ".")
            {
                continue;
            }
            if (str == "..")
            {
                ++pre_cnt;
                continue;
            }
            if (pre_cnt)
            {
                --pre_cnt;
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