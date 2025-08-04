#include <string>

using namespace std;

class Solution 
{
public:
    //1. 双指针
    //很简单，两个指针逐一判断即可
    bool isSubsequence(string s, string t) 
    {
        if (s.size() == 0)
        {
            return true;
        }

        int index = 0;
        for (int i = 0; i < t.size(); ++i)
        {
            if (t[i] == s[index])
            {
                if (++index >= s.size())
                {
                    return true;
                }
            }
        }

        return false;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     string str = "abc";
//     string t = "ahbgdc";
//     bool result = s.isSubsequence(str, t);

//     str = "axc";
//     t = "ahbgdc";
//     result = s.isSubsequence(str, t);

//     return 0;
// }