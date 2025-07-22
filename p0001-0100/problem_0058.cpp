#include <string>

using namespace std;

// https://leetcode.cn/problems/length-of-last-word/

class Solution 
{
public:
    //1. 遍历
    //非空格字符时，累加字符串长度，遇到空格时记录长度即可
    int lengthOfLastWord(string s) 
    {
        int len = 0;
        int temp = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == ' ')
            {
                if (temp != 0)
                {
                    len = temp;
                }
                temp = 0;
            }
            else
            {
                ++temp;
            }
        }

        if (temp != 0)
        {
            len = temp;
        }

        return len;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     string str = "Hello World";
//     int result = s.lengthOfLastWord(str);

//     str = "   fly me   to   the moon  ";
//     result = s.lengthOfLastWord(str);

//     str = "luffy is still joyboy";
//     result = s.lengthOfLastWord(str);

//     return 0;
// }