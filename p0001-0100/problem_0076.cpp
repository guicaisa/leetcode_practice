#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// https://leetcode.cn/problems/minimum-window-substring/

class Solution 
{
public:
    //1. 哈希表+滑动窗口
    //建立两个哈希表，t_map用于统计目标字符串t中各字符的出现次数，s_map用于动态记录当前滑动窗口内相关字符的实际出现次数，引入count计数器，记录窗口内已达到t_map中字符数量的次数
    //不断向右移动滑动窗口的右边界，并将进入窗口并且在t中的字符加入s_map并且计数，当s_map中某个字符的数量累加到与t_map中的数量相等时，count自增，表示该字符已完全覆盖
    //当count等于t_map长度时，即当前滑动窗口已包含t的所有字符，开始收缩滑动窗口，根据当前滑动窗口大小更新最小覆盖字串长度min_lne和起始索引min_pos
    //然后将滑动窗口左边界向右移动以缩小窗口，减少移出的字符在s_map中的数量，如果移出之后该字符在s_map中的数量小于在t_map中的数量，则count递交，表示该字符已不能覆盖
    //重复此过程，直到滑动窗口不满足覆盖条件之后，再回到向右扩展右边界的阶段，遍历完全结束后，返回结果
    string minWindow(string s, string t) 
    {
        //字符串s的长度小于字符串t，则无法覆盖字串
        if (s.size() < t.size())
        {
            return "";
        }
        //构建字符串t关联的哈希表，记录每个字符出现的次数
        unordered_map<char, int> t_map;
        for (int i = 0; i < t.size(); ++i)
        {
            ++t_map[t[i]];
        }

        int index = 0; //滑动窗口左边界
        int min_len = 0; //最小字串长度
        int min_pos = -1; //最小字串启示索引
        int count = 0; //能够覆盖字符串t中的字符个数
        unordered_map<char, int> s_map; //字符串s的滑动窗口关联的哈希表，记录在t中字符出现的次数
        for (int i = 0; i < s.size(); ++i)
        {
            char ch = s[i];
            //该字符不在t中，不处理
            if (t_map.find(ch) == t_map.end())
            {
                continue;
            }
            //自增字符次数，如果自增后数量与t中字符数量相同，则表示能够覆盖该字符个数，count自增
            ++s_map[ch];
            if (s_map[ch] == t_map[ch])
            {
                ++count;
            }
            //如果当前满足覆盖字串的条件，则将滑动窗口左边界向右缩短(判断count和t_map长度即可判断是否能够覆盖字串)
            while (count == t_map.size() && index < s.size())
            {
                //当前滑动窗口长度，尝试更新最短字串长度和字串起始索引
                int len = i - index + 1;
                if (min_len == 0 || len < min_len)
                {
                    min_len = len;
                    min_pos = index;
                }
                //移除滑动窗口的字符
                char index_ch = s[index++];
                //如果该字符在字符串t中，则需要减少s_map中该字符的数量，如果减少之后数量小于字符串t中的数量，则表示不能覆盖字符串个数，count需要自减
                if (t_map.find(index_ch) != t_map.end())
                {
                    if (--s_map[index_ch] < t_map[index_ch])
                    {
                        --count;
                    }
                }
            }
        }
        
        return min_pos == -1 ? "" : s.substr(min_pos, min_len);
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     string str = "ADOBECODEBANC";
//     string t = "ABC";
//     string result = s.minWindow(str, t);

//     return 0;
// }