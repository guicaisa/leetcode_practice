#include <string>

using namespace std;

// https://leetcode.cn/problems/zigzag-conversion/

class Solution 
{
public:
    //1. 遍历
    //首先观察题目描述可以发现，走Z字是有规律，走一轮Z字的长度是 numRows + (numRows - 2)，去掉了头尾两行
    //以这个长度作为offset，可以非常轻松的计算处每行Z字竖边上的所有字符，用 row + x * offset 的方式去算即可
    //关于斜边上的字符，可以依据下一个Z字的顶行字符来逆推，假设下一个Z字顶行首字符在s中的索引是index
    //那么如果斜边上的字符在第二行，该索引就是index-1，根据这种方式可以计算处所有斜边上的字符的索引，从而得到结果
    string convert(string s, int numRows) 
    {
        if (numRows == 1)
        {
            return s;
        }
        
        int offset = numRows + (numRows - 2); //一轮Z字的长度
        string result;
        //按行遍历
        for (int i = 0; i < numRows; ++i)
        {
            //非首位行，Z字斜边上有字符，计算其与下一个Z字顶行字符的索引差值
            int diff = i != 0 && i != numRows - 1 ? i : 0;
            int count = 0; //表示第几个Z字
            while (1)
            {
                //每行竖边上的字符索引
                int n = i + count * offset;
                if (n >= s.size())
                {
                    break;
                }
                result += s[n];
                if (diff != 0)
                {
                    //斜边上的字符索引
                    int m = (count + 1) * offset - diff;
                    if (m < s.size())
                    {
                        result += s[m];
                    }
                }
                ++count;
            }
        }

        return result;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     string str = "PAYPALISHIRING";
//     int numRows = 3;
//     string result = s.convert(str, numRows); 
    
//     str = "PAYPALISHIRING";
//     numRows = 4;
//     result = s.convert(str, numRows);

//     str = "A";
//     numRows = 1;
//     result = s.convert(str, 1);

//     return 0;
// }