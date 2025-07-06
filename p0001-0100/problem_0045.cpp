#include <vector>

using namespace std;

// https://leetcode.cn/problems/jump-game-ii/

class Solution 
{
public:
    //1. 贪心
    //根据当前所在位置和能到达的最远距离，计算下一次可以达到的最远距离
    //每计算一段，就自增一次count，最终得到跳跃次数
    int jump(vector<int>& nums) 
    {
        int count = 0;
        int left = 0;
        int right = 0;
        for (; right < nums.size() - 1; )
        {
            int max_pos = 0;
            for (int i = left; i <= right; ++i)
            {
                max_pos = max(max_pos, i + nums[i]);
            }
            ++count;
            left = right + 1;
            right = max_pos;
        }

        return count;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     vector<int> nums = {2, 3, 1, 1, 4};
//     int result = s.jump(nums);

//     nums = {2, 3, 0, 1, 4};
//     result = s.jump(nums);

//     return 0;
// }