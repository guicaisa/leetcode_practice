#include <unordered_map>

// https://leetcode.cn/problems/happy-number/

using namespace std;

class Solution 
{
public:
    //1. 哈希表
    //根据公式计算下一个n的值，并存入到哈希表中，如果计算出下一个n值为1直接返回正确，如果新计算出的值重复出现在哈希表中，则返回错误
    bool isHappy(int n) 
    {
        unordered_map<int, int> map;
        map[n] = 1;
        while (1)
        {
            int temp = 0;
            while (n > 0)
            {
                int remain = n % 10;
                temp += remain * remain;
                n /= 10;
            }
            if (temp == 1)
            {
                return true;
            }
            if (map.find(temp) != map.end())
            {
                return false;
            }
            map[temp] = 1;
            n = temp;
        }

        return false;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：n = 19
//     //输出：true
//     bool result = s.isHappy(19);

//     //输入：n = 2
//     //输出：false
//     result = s.isHappy(2);

//     return 0;
// }