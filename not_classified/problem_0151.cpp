#include <string>

using namespace std;

// https://leetcode.cn/problems/reverse-words-in-a-string/

class Solution 
{
public:
    string reverseWords(string s) 
    {
        int index = 0;
        bool space_once = true;
        for (int i = 0; i < s.size(); ++i)
        {
            char ch = s[i];
            if (ch == ' ')
            {
                if (space_once)
                {
                    continue;
                }
                space_once = true;
            }
            else
            {
                space_once = false;
            }
            s[index++] = ch;
        }
        s = s.substr(0, index);
        if (s[s.size() - 1] == ' ')
        {
            s = s.substr(0, s.size() - 1);
        }

        reverse(s.begin(), s.end());

        index = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == ' ')
            {
                reverse(s.begin() + index, s.begin() + i);
                index = i + 1;
            }
        }
        reverse(s.begin() + index, s.end());
        return s;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     string str = "the sky is blue";
//     string result = s.reverseWords(str);

//     str = "  hello world  ";
//     result = s.reverseWords(str);

//     str = "a good   example";
//     result = s.reverseWords(str);

//     return 0;
// }