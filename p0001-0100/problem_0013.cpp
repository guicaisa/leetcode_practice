#include <string>
#include <unordered_map>

using namespace std;

// https://leetcode.cn/problems/roman-to-integer/

class Solution {
public:
    Solution() 
    {
        roman_map_['I'] = 1;
        roman_map_['V'] = 5;
        roman_map_['X'] = 10;
        roman_map_['L'] = 50;
        roman_map_['C'] = 100;
        roman_map_['D'] = 500;
        roman_map_['M'] = 1000;
    }

    //1. 反向遍历
    //首先需要维护各个罗马数字和阿拉伯数字的映射，从尾部进行遍历，即从个位数开始
    //由于罗马数字中用IV表示4，IX表示9，根据这种特点可以发现一个规律，当字面值更小的字符出现在字面值较大的字符的左侧的时，表示的是减
    //根据这一特性，我们可以使用一个变量此次字符转换成阿拉伯数字之后是加还是减
    //只需在遍历过程中遇到与之前的字符不同时，通过判断大小就能确定此次累加的符号，完成遍历后，获得最终结果
    int romanToInt(string s) 
    {
        char pre_ch = ' ';
        int sum = 0;
        bool positive = true;
        for (int i = s.size() - 1; i >= 0; --i)
        {
            int cur_int = roman_map_[s[i]];
            //当前字符串与前一个字符不同，根据大小判断正负
            if (pre_ch != s[i])
            {
                int pre_int = roman_map_[pre_ch];
                positive = cur_int > pre_int;
            }
            sum += positive ? 1 * cur_int : -1 * cur_int;
            pre_ch = s[i];
        }

        return sum;
    }

    unordered_map<char, int> roman_map_;
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     string str = "III";
//     int result = s.romanToInt(str);

//     str = "IV";
//     result = s.romanToInt(str);

//     str = "IX";
//     result = s.romanToInt(str);

//     str = "LVIII";
//     result = s.romanToInt(str);

//     str = "MCMXCIV";
//     result = s.romanToInt(str);

//     return 0;
// }