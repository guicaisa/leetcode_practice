#include <vector>

using namespace std;

// https://leetcode.cn/problems/jump-game/

class Solution 
{
public:
    //1. 遍历
    //遍历过程中，不断更新当前可以到达的最远位置max_pos，如果max_pos可以到达数组末尾，则返回true
    //在遍历过程中一旦发现max_pos小于当前遍历的位置，则表示无法到达，返回false
    bool canJump(vector<int>& nums) 
    {
        int max_pos = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (i > max_pos)
            {
                return false;
            }
            //i + nums[i]表示从当前位置上可以到达的最远位置
            max_pos = max(max_pos, i + nums[i]);
            if (max_pos >= nums.size() - 1)
            {
                return true;
            }
        }

        return true;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     vector<int> nums = {2, 3, 1, 1, 4};
//     bool result = s.canJump(nums);

//     nums = {3, 2, 1, 0, 4};
//     result = s.canJump(nums);

//     return 0;
// }