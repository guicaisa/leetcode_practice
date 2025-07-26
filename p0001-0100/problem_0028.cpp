#include <string>

using namespace std;

// https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/

class Solution 
{
public:
    int strStr(string haystack, string needle) 
    {
        int index = 0; //标识haystack中的起始位置
        int j = 0; //表示needle目前遍历的位置
        for (int i = 0; i < haystack.size(); ++i)
        {
            if (haystack[i] == needle[j])
            {
                //needle遍历完了，返回结果
                if (j == needle.size() - 1)
                {
                    return index;
                }
                ++j;
                continue;
            }
            i = index++; //定位到下个起始位置
            j = 0;
            //剩余长度小于needle长度，肯定不匹配，直接返回
            if (haystack.size() - index < needle.size())
            {
                return -1;
            }
        }

        return -1;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     string  haystack = "sadbutsad";
//     string needle = "sad";
//     int result = s.strStr(haystack, needle);

//     haystack = "leetcode";
//     needle = "leeto";
//     result = s.strStr(haystack, needle);

//     return 0;
// }

