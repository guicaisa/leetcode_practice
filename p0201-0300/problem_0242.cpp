#include <string>
#include <unordered_map>

// https://leetcode.cn/problems/valid-anagram/

using namespace std;

class Solution 
{
public:
    //1. 哈希表
    //使用两个哈希表，分别存储s和t中字符出现的数量，然后比较两个哈希表是否完全一致
    bool isAnagram(string s, string t) 
    {
        unordered_map<char, int> smap;
        unordered_map<char, int> tmap;
        for (int i = 0; i < s.size(); ++i)
        {
            ++smap[s[i]];
        }
        for (int i = 0; i < t.size(); ++i)
        {
            ++tmap[t[i]];
        }
        if (smap.size() != tmap.size())
        {
            return false;
        }
        for (auto it = smap.begin(); it != smap.end(); ++it)
        {
            if (it->second != tmap[it->first])
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

//     //输入: s = "anagram", t = "nagaram"
//     //输出: true
//     string str = "anagram";
//     string t = "nagaram";
//     bool result = s.isAnagram(str, t);

//     //输入: s = "rat", t = "car"
//     //输出: false
//     str = "rat";
//     t = "car";
//     result = s.isAnagram(str, t);

//     return 0;
// }