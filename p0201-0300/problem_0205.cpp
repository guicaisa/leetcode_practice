#include <string>
#include <unordered_map>

// https://leetcode.cn/problems/isomorphic-strings/

using namespace std;

class Solution 
{
public:
    //1. 哈希表
    //一个哈希表用来存储s和t中字符的映射关系，如果映射不一致，直接返回报错
    //另一个哈希表用来存储映射的t中的字符，用来判断一个字符被映射多次
    bool isIsomorphic(string s, string t) 
    {
        unordered_map<char, char> map1;
        unordered_map<char, char> map2;
        for (int i = 0; i < s.size(); ++i)
        {
            char sc = s[i];
            char tc = t[i];
            auto it = map1.find(sc);
            if (it != map1.end())
            {
                if (it->second != tc)
                {
                    return false;
                }
            }
            else
            {
                if (map2.find(tc) != map2.end())
                {
                    return false;
                }
                map1[sc] = tc;
                map2[tc] = ' ';
            }
        }

        return true;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：s = "egg", t = "add"
//     //输出：true
//     string str = "egg";
//     string t = "add";
//     bool result = s.isIsomorphic(str, t);

//     //输入：s = "f11", t = "b23"
//     //输出：false
//     str = "f11";
//     t = "b23";
//     result = s.isIsomorphic(str, t);

//     //输入：s = "paper", t = "title"
//     //输出：true
//     str = "paper";
//     t = "title";
//     result = s.isIsomorphic(str, t);


//     return 0;
// }