#include <vector>
#include <unordered_map>

using namespace std;

// https://leetcode.cn/problems/3sum/

class Solution 
{
public:
    //1. 排序+双指针
    //首先对数组进行排序，在遍历的过程中可以去除掉重复元素，不进行处理
    //确定单个元素之后，在剩下的数组中使用双指针来当作双数之和问题处理
    vector<vector<int>> threeSum(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> results;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }
            int num = nums[i];
            if (num > 0)
            {
                break;
            }
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right)
            {
                int left_num = nums[left];
                int right_num = nums[right];
                int sum = num + left_num + right_num;
                if (sum == 0)
                {
                    results.push_back(vector<int>{num, left_num, right_num});
                    while (left < nums.size() && nums[left] == left_num)
                    {
                        ++left;
                    }
                    while (right >= 0 && nums[right] == right_num)
                    {
                        --right;
                    }
                }
                else if (sum < 0)
                {
                    while (left < nums.size() && nums[left] == left_num)
                    {
                        ++left;
                    }
                }
                else 
                {
                    while (right >= 0 && nums[right] == right_num)
                    {
                        --right;
                    }
                }
            }
        }

        return results;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     vector<int> nums = {-1, 0, 1, 2, -1, -4};
//     vector<vector<int>> results = s.threeSum(nums);

//     nums = {0, 1, 1};
//     results = s.threeSum(nums);

//     nums = {0, 0, 0};
//     results = s.threeSum(nums);

//     nums = {0, 0, 0, 0};
//     results = s.threeSum(nums);

//     return 0;
// }