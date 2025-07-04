#include <vector>

using namespace std;

// https://leetcode.cn/problems/jump-game-ii/

class Solution {
public:
    int jump(vector<int>& nums) {
        int count = 0;
        for (int i = 0; i < nums.size();)
        {
            if (nums[i] == 0)
            {
                break;
            }
            int max_dis = 0;
            int max_j = 0;
            for (int j = 1; j <= nums[i]; ++j)
            {
                if (i + j >= nums.size())
                {
                    return ++count;
                }
                if (nums[i+j] + i + j >= nums.size())
                {
                    return ++count;
                }
                if (nums[i+j] + i + j > max_dis)
                {
                    max_dis = nums[i+j] + i + j;
                    max_j = j;
                }
            }
            i = max_dis;
            count++;
        }
        return count;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     vector<int> nums = {2,3,1,1,4};
//     int result = s.jump(nums);

//     return 0;
// }