#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// https://leetcode.cn/problems/minimum-window-substring/

class Solution 
{
public:
    bool isContain(unordered_map<char, int>& char_to_num, unordered_map<char, int>& schar_to_num)
    {
        if (schar_to_num.size() < char_to_num.size())
        {
            return false;
        }
        for (auto it = char_to_num.begin(); it != char_to_num.end(); ++it)
        {
            if (schar_to_num[it->first] < it->second)
            {
                return false;
            }
        }

        return true;
    }

    string minWindow(string s, string t) 
    {
        if (s.size() < t.size())
        {
            return "";
        }
        unordered_map<char, int> char_to_num;
        for (int i = 0; i < t.size(); ++i)
        {
            char ch = t[i];
            ++char_to_num[ch];
        }
        int index = 0;
        unordered_map<char, int> schar_to_num;
        int min_len = 0;
        int min_pos = -1;
        for (int i = 0; i < s.size(); ++i)
        {
            char ch = s[i];
            if (char_to_num.find(ch) == char_to_num.end())
            {
                continue;
            }
            ++schar_to_num[ch];
            while (isContain(char_to_num, schar_to_num))
            {
                int len = i - index + 1;
                if (min_len == 0 || len < min_len)
                {
                    min_len = len;
                    min_pos = index;
                }
                char index_ch = s[index++];
                if (char_to_num.find(index_ch) != char_to_num.end())
                {
                    --schar_to_num[index_ch];
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