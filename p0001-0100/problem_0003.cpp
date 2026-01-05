#include <string>
#include <unordered_map>

// https://leetcode.cn/problems/longest-substring-without-repeating-characters/

using namespace std;

class Solution 
{
public:
    //1. 滑动窗口
    //使用双指针维持一个滑动窗口，左指针固定位置之后，右指针不断向右移动，同时计算滑动窗口的长度，将较大值保存在结果中
    //将遇到的每个字符和其索引记录在哈希表中，当遇到相同字符的时候，变更滑动窗口的左指针
    //将其定位到该字符上次出现的索引+1的位置，然后继续将右指针向右移动进行判断
    //注意在判断字符是否重复出现的时候，不能仅仅判断其是否在哈希表中，如果该字符在哈希表中但其索引处于左指针的左侧
    //即不处于滑动窗口的范围内，则需要将其视为不重复字符
    int lengthOfLongestSubstring(string s) 
    {
        unordered_map<char, int> ch_map;
        int max_len = 0;
        int idx = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            char ch = s[i];
            auto it = ch_map.find(ch);
            //如果ch在哈希表中，但是其索引位置小于idx，则表示其在滑动窗口之外，为不重复字符
            if (it == ch_map.end() || it->second < idx)
            {
                int len = i - idx + 1;
                max_len = max(max_len, len);
            }
            else
            {
                idx = it->second + 1;
            }
            ch_map[ch] = i;
        }

        return max_len;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: s = "abcabcbb"
//     //输出: 3
//     string str = "abcabcbb";
//     int result = s.lengthOfLongestSubstring(str);    

//     //输入: s = "bbbbb"
//     //输出: 1
//     str = "bbbbb";
//     result = s.lengthOfLongestSubstring(str);

//     //输入: s = "pwwkew"
//     //输出: 3
//     str = "pwwkew";
//     result = s.lengthOfLongestSubstring(str);

//     str = "tmmzuxt";
//     result = s.lengthOfLongestSubstring(str);

//     return 0;
// }