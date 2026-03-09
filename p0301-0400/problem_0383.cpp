#include <string>
#include <unordered_map>

// https://leetcode.cn/problems/ransom-note/

using namespace std;

class Solution 
{
public:
    //1. 哈希表
    //本质是判断magazine中的字符频次是否能完全覆盖ransomNote的需求
    //分别为ransomNote和magazine构造2个哈希表s_map和m_map，记录每个字符出现的次数
    //遍历s_map，检查其中每个字符数量与m_map该字符的数量，如果m_map中该字符数量小于s_map中的数量，则表示不能覆盖，直接返回错误
    bool canConstruct(string ransomNote, string magazine) 
    {
        unordered_map<char, int> r_map;
        unordered_map<char, int> m_map;
        for (int i = 0; i < ransomNote.size(); ++i)
        {
            ++r_map[ransomNote[i]];
        }
        for (int i = 0; i < magazine.size(); ++i)
        {
            ++m_map[magazine[i]];
        }
        for (auto it = r_map.begin(); it != r_map.end(); ++it)
        {
            if (m_map[it->first] < it->second)
            {
                return false;
            }
        }
        return true;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：ransomNote = "a", magazine = "b"
//     //输出：false
//     string ransomNote = "a";
//     string magazine = "b";
//     bool result = s.canConstruct(ransomNote, magazine);

//     //输入：ransomNote = "aa", magazine = "ab"
//     //输出：false
//     ransomNote = "aa";
//     magazine = "ab";
//     result = s.canConstruct(ransomNote, magazine);

//     //输入：ransomNote = "aa", magazine = "aab"
//     //输出：true
//     ransomNote = "aa";
//     magazine = "aab";
//     result = s.canConstruct(ransomNote, magazine);

//     return 0;
// }