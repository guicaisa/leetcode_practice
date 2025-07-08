#include <vector>

using namespace std;

// https://leetcode.cn/problems/minimum-size-subarray-sum/

class Solution 
{
public:
    int minSubArrayLen(int target, vector<int>& nums) 
    {
        int left = 0;
        int right = 0;
        int min_len = 0;
        int sum = 0;
        while (right < nums.size())
        {
            if (sum < target)
            {
                sum += nums[right++];
            }
            while (sum >= target)
            {
                int len = right - left;
                min_len = min_len == 0 ? len : min(min_len, len);
                sum -= nums[left++];
            }
        }
        
        return min_len;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     vector<int> nums = {2, 3, 1, 2, 4, 3};
//     int result = s.minSubArrayLen(7, nums);

//     return 0;
// }