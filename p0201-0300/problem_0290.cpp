#include <string>
#include <unordered_map>

// https://leetcode.cn/problems/word-pattern/

using namespace std;

class Solution 
{
public:
    //1. 哈希表
    //使用2个哈希表，一个记录字符到字符串的映射，一个记录字符串到字符的映射
    //遍历s，截取每个字符串，然后获取当前遍历到的pattern中的字符，如果已记录映射关系并且映射的值不相符，则直接返回报错
    //注意遍历完s之后，需要判断pattern的所有字符是否已被遍历到，不然映射关系数量不一致，也需要报错
    bool wordPattern(string pattern, string s) 
    {
        unordered_map<char, string> ch2str;
        unordered_map<string, char> str2ch;
        int index = 0;
        int str_index = 0;
        for (int i = 0; i < s.size(); )
        {
            if (i == s.size() - 1 || s[i+1] == ' ')
            {
                if (index >= pattern.size())
                {
                    return false;
                }
                char ch = pattern[index];
                string str = s.substr(str_index, i - str_index + 1);
                auto itc = ch2str.find(ch);
                auto its = str2ch.find(str);
                if (itc != ch2str.end() && itc->second != str)
                {
                    return false;
                }
                if (its != str2ch.end() && its->second != ch)
                {
                    return false;
                }
                ch2str[ch] = str;
                str2ch[str] = ch;

                ++index;
                i = i + 2;
                str_index = i;
            }
            else
            {
                ++i;
            }
        }
        return index >= pattern.size();
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: pattern = "abba", s = "dog cat cat dog"
//     //输出: true
//     string pattern = "abba";
//     string str = "dog cat cat dog";
//     bool result = s.wordPattern(pattern, str);

//     //输入:pattern = "abba", s = "dog cat cat fish"
//     //输出: false
//     pattern = "abba";
//     str = "dog cat cat fish";
//     result = s.wordPattern(pattern, str);

//     //输入: pattern = "aaaa", s = "dog cat cat dog"
//     //输出: false
//     pattern = "aaaa";
//     str = "dog cat cat dog";
//     result = s.wordPattern(pattern, str);

//     return 0;
// }