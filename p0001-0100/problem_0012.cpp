#include <string>
#include <unordered_map>

using namespace std;

// https://leetcode.cn/problems/integer-to-roman/

class Solution 
{
public:
    Solution() {
        unordered_map<int, char> temp = {
            {1, 'I'},
            {5, 'V'},
            {10, 'X'}
        };
        nmap_[1] = temp;

        temp = {
            {1, 'X'},
            {5, 'L'},
            {10, 'C'}
        };
        nmap_[10] = temp;

        temp = {
            {1, 'C'},
            {5, 'D'},
            {10, 'M'}
        };
        nmap_[100] = temp;

        temp = {
            {1, 'M'}
        };
        nmap_[1000] = temp;
    }

    //1. 按位处理
    //从个位数开始处理每个进位上的数字，特殊处理下4和9即可
    string intToRoman(int num) 
    {
        string result;
        int step = 1; //当前进位(个十百千)
        while (num)
        {
            int temp = num % 10;
            switch (temp)
            {
                case 0:
                break;
                case 4: //数字4特殊处理，例如IV
                result = nmap_[step][5] + result;
                result = nmap_[step][1] + result;
                break;
                case 9: //数字9特殊处理，例如IX
                result = nmap_[step][10] + result;
                result = nmap_[step][1] + result;
                break;
                default:
                string t;
                //先加个5
                if (temp >= 5)
                {
                    t += nmap_[step][5];
                    temp %= 5;
                }
                //再加剩下的temp个1
                for (int i = 0; i < temp; ++i)
                {
                    t += nmap_[step][1];
                }
                result = t + result;
                break;
            }
            //进位
            step *= 10; 
            num /= 10;
        }

        return result;
    }

    unordered_map<int, unordered_map<int, char>> nmap_;
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     int num = 3749;
//     string result = s.intToRoman(num);

//     num = 58;
//     result = s.intToRoman(num);
    
//     num = 1994;
//     result = s.intToRoman(num);

//     return 0;
// }